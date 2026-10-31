import unittest

import numpy as np

import rcsim


class SmoothingTest(unittest.TestCase):
    def test_vinterp_matches_engine_formula(self):
        cur, tgt = np.array([0.0, 0.0]), np.array([100.0, 0.0])
        out = rcsim.vinterp_to(cur, tgt, 1 / 60, 10.0)
        np.testing.assert_allclose(out, [100.0 * 10.0 / 60, 0.0])
        # step clamps to the target when dt * speed >= 1
        np.testing.assert_allclose(rcsim.vinterp_to(cur, tgt, 0.2, 10.0), tgt)

    def test_offset_smoother_does_not_lag_constant_motion(self):
        sm = rcsim.OffsetSmoother()
        v = np.array([600.0, 0.0])
        for k in range(200):
            est = v * k / 60
            out = sm(est, v, 1 / 60, corrected=True)
        np.testing.assert_allclose(out, est, atol=1e-6)


class LinkTest(unittest.TestCase):
    def _snaps(self, n=200):
        return [rcsim.Snapshot(i / 60, np.zeros(2), np.zeros(2)) for i in range(1, n)]

    def _delivered(self, fifo):
        cfg = rcsim.NetConfig(latency=0.3, fifo_queue=fifo)
        link = rcsim.Link(self._snaps(), cfg, np.random.default_rng(0))
        got = []
        for t in np.arange(0, 5, 1 / 60):
            got += [s.ts for s, _ in link.poll(t)]
        return got

    def test_fifo_queue_never_reorders(self):
        got = self._delivered(fifo=True)
        self.assertEqual(got, sorted(got))

    def test_per_packet_delivery_reorders_under_jitter(self):
        got = self._delivered(fifo=False)
        self.assertNotEqual(got, sorted(got))

    def test_loss_rate(self):
        cfg = rcsim.NetConfig(loss=0.4)
        link = rcsim.Link(self._snaps(5000), cfg, np.random.default_rng(1))
        n = len(link.poll(1e9))
        self.assertAlmostEqual(n / 4999, 0.6, delta=0.03)


class ClockTest(unittest.TestCase):
    def test_ping_offset_close_to_truth(self):
        cfg = rcsim.NetConfig(latency=0.3)
        link = rcsim.Link([], cfg, np.random.default_rng(2))
        clock = rcsim.PingClock(link, client_offset=4.0)
        for t in np.arange(0, 20, 1 / 60):
            clock.update(t)
        # symmetric model: error bounded by half the jitter range
        self.assertLess(abs(clock.estimate - 4.0), 0.3 * rcsim.JITTER_FRACTION)

    def test_original_sync_is_biased_by_latency(self):
        c = rcsim.OriginalClient()
        snap = rcsim.Snapshot(10.0, np.zeros(2), np.zeros(2))
        c.receive(snap, client_time=10.0 - 4.0 + 0.3)  # arrived 0.3 s late
        self.assertAlmostEqual(c.offset, 4.0 - 0.3)


class BufferTest(unittest.TestCase):
    def test_sorted_buffer_orders_and_dedups(self):
        b = rcsim.SortedBuffer()
        for ts in [0.3, 0.1, 0.2, 0.2]:
            b.add(rcsim.Snapshot(ts, np.zeros(2), np.zeros(2)))
        self.assertEqual(b.ts, [0.1, 0.2, 0.3])


class KalmanTest(unittest.TestCase):
    def test_tracks_constant_velocity(self):
        kf = rcsim.KalmanCV(q=1e4, pos_sigma=10.0, vel_sigma=60.0)
        rng = np.random.default_rng(3)
        v = np.array([600.0, -300.0])
        for k in range(300):
            t = k / 60
            kf.update(rcsim.Snapshot(t, v * t + rng.normal(0, 10, 2),
                                     v + rng.normal(0, 60, 2)))
        pos, vel = kf.predict(5.0)
        np.testing.assert_allclose(vel, v, atol=20)
        np.testing.assert_allclose(pos, v * 5.0, atol=20)

    def test_rejects_stale_packet(self):
        kf = rcsim.KalmanCV(q=1e4, pos_sigma=1.0, vel_sigma=1.0)
        kf.update(rcsim.Snapshot(1.0, np.zeros(2), np.zeros(2)))
        self.assertFalse(kf.update(rcsim.Snapshot(0.5, np.ones(2), np.zeros(2))))


class EndToEndTest(unittest.TestCase):
    def test_same_motion_for_every_method(self):
        a = rcsim.run("off", rcsim.NetConfig(0.1, 0.2), seed=5, duration=10)
        b = rcsim.run("dr_present", rcsim.NetConfig(0.1, 0.2), seed=5, duration=10)
        n = min(len(a.t), len(b.t))
        np.testing.assert_allclose(a.server[-n:], b.server[-n:])

    def test_perfect_network_present_error_small(self):
        res = rcsim.run("dr_present", rcsim.NetConfig(), seed=6, duration=20)
        # one frame of motion at 600 cm/s is 10-12 cm
        self.assertLess(res.metrics["err_mean"], 15.0)

    def test_original_error_matches_interpolation_delay(self):
        res = rcsim.run("original", rcsim.NetConfig(), seed=7, duration=30)
        # 0.7 s behind at 600 cm/s, shortened at turns
        self.assertGreater(res.metrics["err_mean"], 300.0)
        self.assertLess(res.metrics["err_mean"], 0.8 * rcsim.AGENT_SPEED)


if __name__ == "__main__":
    unittest.main()
