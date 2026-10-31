"""Offline replay of the Realtime-Consistency-Sim network experiment.

The Unreal project moves an authoritative agent on the server, sends
position/velocity snapshots over UDP with injected latency, jitter and loss,
and reconstructs the agent on the client. This module rebuilds that pipeline
in plain Python so the reconstruction methods can be compared over many
network conditions and seeds without running the engine.

`OriginalClient` follows Source/NetSimProject/Private/NetworkAgent.cpp and
ANetworkManager.cpp line by line (first-packet clock sync, FIFO delay queue,
0.7 s interpolation delay, 0.5 s gap limit, constant-velocity dead reckoning,
VInterpTo correction). The other clients change one part at a time.

Units follow the engine: centimetres and seconds.
"""

from __future__ import annotations

import bisect
import math
from dataclasses import dataclass, field

import numpy as np

AGENT_SPEED = 600.0          # ANetworkManager::RunServerSimulation
WAYPOINT_RADIUS = 100.0      # waypoint reached when closer than this
PATHFINDING_RADIUS = 2000.0  # AANetworkManager::PathfindingRadius
MAP_HALF_SIZE = 4000.0       # bounds of the replayed floor
JITTER_FRACTION = 0.2        # latency * RandRange(-0.2, 0.2)
INTERP_DELAY = 0.7           # ANetworkAgent::InterpolationDelay
MAX_INTERP_GAP = 0.5
CORRECTION_SPEED = 10.0      # VInterpTo speed
BUFFER_SIZE = 50

STATE_OFF, STATE_INTERP, STATE_DR = 0, 1, 2


# ---------------------------------------------------------------------------
# Server trajectory


@dataclass
class Trajectory:
    t: np.ndarray    # server tick times (server clock == true time)
    pos: np.ndarray  # (N, 2)
    vel: np.ndarray  # (N, 2)

    def position_at(self, time: float) -> np.ndarray:
        """Position of the last server tick at or before `time`."""
        i = int(np.searchsorted(self.t, time, side="right")) - 1
        return self.pos[max(i, 0)]


def frame_times(duration: float, rng: np.random.Generator,
                fps_min: float = 50.0, fps_max: float = 70.0) -> np.ndarray:
    """Variable engine frame times, as both UE processes tick per frame."""
    n = int(duration * fps_max) + 10
    dt = rng.uniform(1.0 / fps_max, 1.0 / fps_min, size=n)
    t = np.cumsum(dt)
    return t[t <= duration]


def random_target(origin: np.ndarray, rng: np.random.Generator) -> np.ndarray:
    """Random reachable point within PATHFINDING_RADIUS, kept on the floor."""
    while True:
        r = PATHFINDING_RADIUS * math.sqrt(rng.uniform())
        a = rng.uniform(0.0, 2.0 * math.pi)
        p = origin + r * np.array([math.cos(a), math.sin(a)])
        if np.all(np.abs(p) < MAP_HALF_SIZE):
            return p


def server_trajectory(duration: float, rng: np.random.Generator) -> Trajectory:
    """Move the agent like RunServerSimulation: head to the current path point
    at 600 cm/s, switch point when within 100 cm, pick a new random target when
    the path is done. The replayed floor is open, so a path is one segment."""
    ticks = frame_times(duration, rng)
    pos = np.zeros(2)
    target = random_target(pos, rng)
    out_p = np.empty((len(ticks), 2))
    out_v = np.empty((len(ticks), 2))
    prev = 0.0
    for k, t in enumerate(ticks):
        dt = t - prev
        prev = t
        if np.linalg.norm(target - pos) < WAYPOINT_RADIUS:
            target = random_target(pos, rng)
        d = target - pos
        n = np.linalg.norm(d)
        vel = d / n * AGENT_SPEED if n > 1e-6 else np.zeros(2)
        pos = pos + vel * dt
        out_p[k] = pos
        out_v[k] = vel
    return Trajectory(ticks, out_p, out_v)


# ---------------------------------------------------------------------------
# Network


@dataclass
class Snapshot:
    ts: float
    pos: np.ndarray
    vel: np.ndarray


@dataclass
class NetConfig:
    latency: float = 0.0       # one-way, seconds
    loss: float = 0.0          # drop probability per snapshot
    send_hz: float | None = None  # None: one snapshot per server tick
    fifo_queue: bool = True    # original delay queue pops only from the front
    pos_noise: float = 0.0     # optional measurement noise on sent state
    vel_noise: float = 0.0


def make_snapshots(traj: Trajectory, cfg: NetConfig,
                   rng: np.random.Generator) -> list[Snapshot]:
    if cfg.send_hz is None:
        idx = np.arange(len(traj.t))
    else:
        send_t = np.arange(0.0, traj.t[-1], 1.0 / cfg.send_hz)
        idx = np.unique(np.searchsorted(traj.t, send_t, side="right") - 1)
        idx = idx[idx >= 0]
    snaps = []
    for i in idx:
        p = traj.pos[i].copy()
        v = traj.vel[i].copy()
        if cfg.pos_noise:
            p += rng.normal(0.0, cfg.pos_noise, 2)
        if cfg.vel_noise:
            v += rng.normal(0.0, cfg.vel_noise, 2)
        snaps.append(Snapshot(float(traj.t[i]), p, v))
    return snaps


class Link:
    """Server -> client path. Packets reach the socket instantly (localhost)
    and are read on the next client frame; loss and delay are applied there,
    as in AANetworkManager::ProcessIncomingPackets / DispatchDelayedPackets."""

    def __init__(self, snaps: list[Snapshot], cfg: NetConfig,
                 rng: np.random.Generator):
        self.snaps = snaps
        self.cfg = cfg
        self.rng = rng
        self.next_idx = 0
        self.queue: list[tuple[float, int, Snapshot]] = []  # (process_time, seq, snap)
        self.seq = 0

    def poll(self, true_time: float) -> list[tuple[Snapshot, float]]:
        """Return snapshots handed to the client at this frame with the true
        time they were read from the socket (for delay statistics)."""
        cfg = self.cfg
        while self.next_idx < len(self.snaps) and self.snaps[self.next_idx].ts <= true_time:
            s = self.snaps[self.next_idx]
            self.next_idx += 1
            if self.rng.uniform() < cfg.loss:
                continue
            jitter = cfg.latency * self.rng.uniform(-JITTER_FRACTION, JITTER_FRACTION)
            item = (true_time + cfg.latency + jitter, self.seq, s)
            self.seq += 1
            if cfg.fifo_queue:
                self.queue.append(item)
            else:
                bisect.insort(self.queue, item)
        out = []
        while self.queue and self.queue[0][0] <= true_time:
            out.append((self.queue.pop(0)[2], true_time))
        return out

    def sample_delay(self) -> float:
        """One-way delay for a ping packet under the same latency model."""
        lat = self.cfg.latency
        return lat + lat * self.rng.uniform(-JITTER_FRACTION, JITTER_FRACTION)


# ---------------------------------------------------------------------------
# Smoothing


def vinterp_to(current: np.ndarray, target: np.ndarray, dt: float,
               speed: float) -> np.ndarray:
    """FMath::VInterpTo."""
    if speed <= 0.0:
        return target.copy()
    dist = target - current
    if float(dist @ dist) < 1e-8:
        return target.copy()
    return current + dist * min(max(dt * speed, 0.0), 1.0)


class OffsetSmoother:
    """Hide correction jumps without lagging steady motion: when a new
    snapshot moves the estimate, keep the old visual position as an offset and
    let that offset decay exponentially."""

    def __init__(self, rate: float = CORRECTION_SPEED):
        self.rate = rate
        self.offset = np.zeros(2)
        self.prev_est: np.ndarray | None = None
        self.prev_vel = np.zeros(2)

    def __call__(self, est: np.ndarray, vel: np.ndarray, dt: float,
                 corrected: bool) -> np.ndarray:
        if self.prev_est is not None and corrected:
            expected = self.prev_est + self.prev_vel * dt
            self.offset += expected - est
        self.offset *= math.exp(-self.rate * dt)
        self.prev_est = est.copy()
        self.prev_vel = vel.copy()
        return est + self.offset


# ---------------------------------------------------------------------------
# Clients


class OriginalClient:
    """NetworkAgent.cpp with bIsEnablePrediction = true (or false for OFF)."""

    name = "original"

    def __init__(self, prediction: bool = True):
        self.prediction = prediction
        self.pos = np.zeros(2)
        self.vel = np.zeros(2)
        self.synced = False
        self.offset = 0.0
        self.buffer: list[Snapshot] = []
        self.last_valid: Snapshot | None = None
        self.dr = False
        self.started = False

    def receive(self, s: Snapshot, client_time: float) -> None:
        if not self.synced:
            self.offset = s.ts - client_time  # includes the packet's latency
            self.synced = True
        if not self.started:
            self.pos = s.pos.copy()
            self.started = True
        if self.prediction:
            self.buffer.append(s)
            if self.last_valid is None or s.ts > self.last_valid.ts:
                self.last_valid = s
            if len(self.buffer) > BUFFER_SIZE:
                self.buffer.pop(0)
        else:
            self.pos = s.pos.copy()
            self.buffer.clear()

    def tick(self, client_time: float, dt: float, corrected: bool) -> None:
        if not (self.prediction and self.synced and self.buffer):
            return
        render = client_time + self.offset - INTERP_DELAY
        buf = self.buffer
        if buf[0].ts > render:
            self.pos = vinterp_to(self.pos, buf[0].pos, dt, CORRECTION_SPEED)
            return
        new_pos = self.pos.copy()
        new_vel = np.zeros(2)
        found = False
        dr_snap = self.last_valid
        for i in range(len(buf) - 1):
            a, b = buf[i], buf[i + 1]
            if a.ts <= render < b.ts:
                gap = b.ts - a.ts
                if gap > MAX_INTERP_GAP:
                    dr_snap = a
                    break
                alpha = (render - a.ts) / gap if gap > 1e-4 else 0.0
                new_pos = a.pos + alpha * (b.pos - a.pos)
                new_vel = a.vel + alpha * (b.vel - a.vel)
                found = True
                self.dr = False
                break
        if not found and dr_snap is not None and dr_snap.ts > 0.0:
            self.dr = True
            since = render - dr_snap.ts
            if since > 0:
                new_pos = dr_snap.pos + dr_snap.vel * since
                new_vel = dr_snap.vel
        self.pos = vinterp_to(self.pos, new_pos, dt, CORRECTION_SPEED)
        self.vel = new_vel

    def state(self) -> int:
        if not self.prediction:
            return STATE_OFF
        return STATE_DR if self.dr else STATE_INTERP


class PingClock:
    """NTP-style offset estimate: one ping per second, keep the sample with
    the smallest round trip among the last few."""

    def __init__(self, link: Link, client_offset: float, period: float = 1.0,
                 window: int = 8):
        self.link = link
        self.client_offset = client_offset  # true_time = client_time + client_offset
        self.period = period
        self.window = window
        self.samples: list[tuple[float, float]] = []  # (rtt, offset)
        self.pending: list[tuple[float, float, float]] = []  # (arrive_true, c0, s1)
        self.next_ping = 0.0
        self.estimate: float | None = None

    def update(self, true_time: float) -> None:
        if true_time >= self.next_ping:
            c0 = true_time - self.client_offset
            up = self.link.sample_delay()
            down = self.link.sample_delay()
            s1 = true_time + up
            self.pending.append((true_time + up + down, c0, s1))
            self.next_ping = true_time + self.period
        still = []
        for arrive, c0, s1 in self.pending:
            if arrive <= true_time:
                c2 = true_time - self.client_offset
                self.samples.append((c2 - c0, s1 - (c0 + c2) / 2.0))
                self.samples = self.samples[-self.window:]
                self.estimate = min(self.samples)[1]
            else:
                still.append((arrive, c0, s1))
        self.pending = still


class SortedBuffer:
    def __init__(self, keep: float = 3.0):
        self.keep = keep
        self.ts: list[float] = []
        self.snaps: list[Snapshot] = []

    def add(self, s: Snapshot) -> None:
        i = bisect.bisect_left(self.ts, s.ts)
        if i < len(self.ts) and self.ts[i] == s.ts:
            return
        self.ts.insert(i, s.ts)
        self.snaps.insert(i, s)
        while self.ts and self.ts[-1] - self.ts[0] > self.keep:
            self.ts.pop(0)
            self.snaps.pop(0)

    def latest(self) -> Snapshot | None:
        return self.snaps[-1] if self.snaps else None


class InterpClient:
    """Interpolation + dead reckoning with the timing fixes: ping-based clock
    sync and a timestamp-sorted buffer. `delay` is either a fixed render delay
    or None for an adaptive delay taken from observed one-way delays."""

    def __init__(self, clock: PingClock, delay: float | None = INTERP_DELAY,
                 smoothing: str = "vinterp", margin_intervals: float = 2.0):
        self.clock = clock
        self.fixed_delay = delay
        self.delay = delay if delay is not None else 0.2
        self.smoothing = smoothing
        self.margin_intervals = margin_intervals
        self.buf = SortedBuffer()
        self.delays: list[float] = []
        self.intervals: list[float] = []
        self.pos = np.zeros(2)
        self.started = False
        self.dr = False
        self.smoother = OffsetSmoother()
        self.name = "interp_adaptive" if delay is None else f"interp_{delay:g}s"

    def receive(self, s: Snapshot, client_time: float) -> None:
        if self.clock.estimate is not None:
            self.delays.append(client_time + self.clock.estimate - s.ts)
            self.delays = self.delays[-120:]
        last = self.buf.latest()
        if last is not None and s.ts > last.ts:
            self.intervals.append(s.ts - last.ts)
            self.intervals = self.intervals[-120:]
        self.buf.add(s)
        if not self.started:
            self.pos = s.pos.copy()
            self.started = True

    def _target_delay(self) -> float:
        d95 = float(np.percentile(self.delays, 95))
        step = float(np.median(self.intervals)) if self.intervals else 1 / 60
        return d95 + self.margin_intervals * step

    def tick(self, client_time: float, dt: float, corrected: bool) -> None:
        if self.clock.estimate is None or not self.buf.snaps:
            return
        if self.fixed_delay is None and len(self.delays) >= 10:
            # change playback delay gradually (at most 10 % of real time)
            target = self._target_delay()
            step = max(-0.1 * dt, min(0.1 * dt, target - self.delay))
            self.delay += step
        render = client_time + self.clock.estimate - self.delay
        ts, snaps = self.buf.ts, self.buf.snaps
        i = bisect.bisect_right(ts, render) - 1
        if i < 0:
            est, vel = snaps[0].pos.copy(), np.zeros(2)
            self.dr = False
        elif i + 1 < len(ts) and ts[i + 1] - ts[i] <= MAX_INTERP_GAP:
            a, b = snaps[i], snaps[i + 1]
            gap = b.ts - a.ts
            alpha = (render - a.ts) / gap if gap > 1e-4 else 0.0
            est = a.pos + alpha * (b.pos - a.pos)
            vel = a.vel + alpha * (b.vel - a.vel)
            self.dr = False
        else:
            a = snaps[i]
            est = a.pos + a.vel * (render - a.ts)
            vel = a.vel
            self.dr = True
        self.pos = smooth(self, est, vel, dt, corrected)

    def state(self) -> int:
        return STATE_DR if self.dr else STATE_INTERP


class KalmanCV:
    """Constant-velocity Kalman filter on [x, y, vx, vy] with white-noise
    acceleration; measurements are the snapshot position and velocity."""

    def __init__(self, q: float, pos_sigma: float, vel_sigma: float):
        self.q = q
        self.R = np.diag([pos_sigma ** 2] * 2 + [vel_sigma ** 2] * 2)
        self.x: np.ndarray | None = None
        self.P = np.eye(4)
        self.t = 0.0

    def _fq(self, dt: float) -> tuple[np.ndarray, np.ndarray]:
        F = np.eye(4)
        F[0, 2] = F[1, 3] = dt
        q = self.q
        Q = np.zeros((4, 4))
        Q[0, 0] = Q[1, 1] = q * dt ** 3 / 3
        Q[0, 2] = Q[2, 0] = Q[1, 3] = Q[3, 1] = q * dt ** 2 / 2
        Q[2, 2] = Q[3, 3] = q * dt
        return F, Q

    def update(self, s: Snapshot) -> bool:
        z = np.concatenate([s.pos, s.vel])
        if self.x is None:
            self.x = z.copy()
            self.P = self.R.copy()
            self.t = s.ts
            return True
        dt = s.ts - self.t
        if dt <= 0:
            return False  # stale or duplicate packet
        F, Q = self._fq(dt)
        x = F @ self.x
        P = F @ self.P @ F.T + Q
        S = P + self.R
        K = P @ np.linalg.inv(S)
        self.x = x + K @ (z - x)
        self.P = (np.eye(4) - K) @ P
        self.t = s.ts
        return True

    def predict(self, t: float) -> tuple[np.ndarray, np.ndarray]:
        h = t - self.t
        return self.x[:2] + self.x[2:] * h, self.x[2:].copy()


class PresentClient:
    """Show the agent at the estimated current server time instead of in the
    past: extrapolate from the newest snapshot (dead reckoning) or from a
    Kalman filter state."""

    def __init__(self, clock: PingClock, kalman: KalmanCV | None = None,
                 smoothing: str = "offset"):
        self.clock = clock
        self.kf = kalman
        self.smoothing = smoothing
        self.newest: Snapshot | None = None
        self.pos = np.zeros(2)
        self.started = False
        self.smoother = OffsetSmoother()
        self.horizons: list[float] = []
        self.name = "kf_present" if kalman else "dr_present"

    def receive(self, s: Snapshot, client_time: float) -> None:
        if self.kf is not None:
            self.kf.update(s)
        if self.newest is None or s.ts > self.newest.ts:
            self.newest = s
        if not self.started:
            self.pos = s.pos.copy()
            self.started = True

    def tick(self, client_time: float, dt: float, corrected: bool) -> None:
        if self.clock.estimate is None or self.newest is None:
            return
        now = client_time + self.clock.estimate
        if self.kf is not None:
            est, vel = self.kf.predict(now)
            self.horizons.append(now - self.kf.t)
        else:
            s = self.newest
            est, vel = s.pos + s.vel * (now - s.ts), s.vel
            self.horizons.append(now - s.ts)
        self.pos = smooth(self, est, vel, dt, corrected)

    def state(self) -> int:
        return STATE_DR


def smooth(client, est, vel, dt, corrected):
    if client.smoothing == "vinterp":
        return vinterp_to(client.pos, est, dt, CORRECTION_SPEED)
    if client.smoothing == "offset":
        return client.smoother(est, vel, dt, corrected)
    return est


# ---------------------------------------------------------------------------
# Run


@dataclass
class RunResult:
    t: np.ndarray
    client: np.ndarray
    server: np.ndarray
    state: np.ndarray
    metrics: dict = field(default_factory=dict)


def accel_magnitude(t: np.ndarray, p: np.ndarray) -> np.ndarray:
    """Second derivative on a non-uniform grid."""
    h1 = t[1:-1] - t[:-2]
    h2 = t[2:] - t[1:-1]
    a = 2.0 * (h1[:, None] * p[2:] - (h1 + h2)[:, None] * p[1:-1]
               + h2[:, None] * p[:-2]) / (h1 * h2 * (h1 + h2))[:, None]
    return np.linalg.norm(a, axis=1)


def summarize(res: RunResult, warmup: float) -> dict:
    m = res.t >= warmup
    err = np.linalg.norm(res.client - res.server, axis=1)[m]
    acc = accel_magnitude(res.t, res.client)[m[1:-1]]
    return {
        "err_mean": float(err.mean()),
        "err_rmse": float(np.sqrt((err ** 2).mean())),
        "err_p95": float(np.percentile(err, 95)),
        "err_max": float(err.max()),
        "dr_frac": float((res.state[m] == STATE_DR).mean()),
        "acc_mean": float(acc.mean()),
        "acc_p99": float(np.percentile(acc, 99)),
    }


def build_client(method: str, link: Link, client_offset: float,
                 kf_q: float = 1e5, pos_sigma: float = 1.0,
                 vel_sigma: float = 5.0):
    if method == "off":
        return OriginalClient(prediction=False), None
    if method == "original":
        return OriginalClient(prediction=True), None
    clock = PingClock(link, client_offset)
    if method == "interp_0.7s":
        return InterpClient(clock, delay=INTERP_DELAY), clock
    if method == "interp_adaptive":
        return InterpClient(clock, delay=None, smoothing="offset"), clock
    if method == "dr_present":
        return PresentClient(clock), clock
    if method == "kf_present":
        return PresentClient(clock, KalmanCV(kf_q, pos_sigma, vel_sigma)), clock
    raise ValueError(method)


def run(method: str, net: NetConfig, seed: int, duration: float = 65.0,
        warmup: float = 5.0, **client_kw) -> RunResult:
    """Replay one recording. Trajectory and network randomness depend only on
    the seed, so every method sees the same server motion."""
    traj = server_trajectory(duration, np.random.default_rng([seed, 0]))
    snaps = make_snapshots(traj, net, np.random.default_rng([seed, 1]))
    link = Link(snaps, net, np.random.default_rng([seed, 2]))
    frng = np.random.default_rng([seed, 3])
    client_offset = float(frng.uniform(2.0, 10.0))  # client process started later
    frames = frame_times(duration, frng)

    client, clock = build_client(method, link, client_offset, **client_kw)
    t_out, c_out, s_out, st_out = [], [], [], []
    prev = frames[0]
    for t in frames:
        dt = t - prev
        prev = t
        ct = t - client_offset
        if clock is not None:
            clock.update(t)
        arrived = link.poll(t)
        for s, _ in arrived:
            client.receive(s, ct)
        client.tick(ct, dt, bool(arrived))
        if not getattr(client, "started", False):
            continue
        t_out.append(t)
        c_out.append(client.pos.copy())
        s_out.append(traj.position_at(t))
        st_out.append(client.state())
    res = RunResult(np.array(t_out), np.array(c_out), np.array(s_out),
                    np.array(st_out))
    res.metrics = summarize(res, warmup)
    return res
