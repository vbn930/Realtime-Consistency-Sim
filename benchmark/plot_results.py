"""Draw the README figure from results/summary.csv."""

from __future__ import annotations

import csv
import os

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt  # noqa: E402

HERE = os.path.dirname(__file__)
SURFACE = "#fcfcfb"
TEXT = "#0b0b0b"
TEXT_2 = "#52514e"
GRID = "#e4e3df"
# mean |acceleration| of the server trajectory itself (10 seeds),
# from rcsim.accel_magnitude on rcsim.server_trajectory
SERVER_ACC = 380.0
# categorical slots in fixed order
METHODS = [
    ("off", "OFF (snap to latest)", "#2a78d6"),
    ("original", "Original (UE code)", "#eb6834"),
    ("interp_0.7s", "Interp 0.7 s + ping sync", "#1baf7a"),
    ("interp_adaptive", "Interp, adaptive delay", "#eda100"),
    ("dr_present", "Extrapolate to present", "#e87ba4"),
]


def load(loss_pct: int):
    rows = list(csv.DictReader(open(os.path.join(HERE, "results", "summary.csv"))))
    data = {}
    for r in rows:
        if r["study"] == "grid" and int(r["loss_pct"]) == loss_pct:
            data.setdefault(r["method"], []).append(
                (int(r["latency_ms"]), float(r["err_mean"]), float(r["acc_mean"])))
    return {k: sorted(v) for k, v in data.items()}


def style(ax, title, ylabel):
    ax.set_facecolor(SURFACE)
    ax.set_title(title, loc="left", color=TEXT, fontsize=11)
    ax.set_xlabel("One-way latency (ms)", color=TEXT_2)
    ax.set_ylabel(ylabel, color=TEXT_2)
    ax.set_yscale("log")
    ax.grid(True, which="major", color=GRID, linewidth=0.8)
    ax.tick_params(colors=TEXT_2)
    for s in ("top", "right"):
        ax.spines[s].set_visible(False)
    for s in ("left", "bottom"):
        ax.spines[s].set_color(GRID)


def main():
    loss = 20
    data = load(loss)
    fig, (a1, a2) = plt.subplots(1, 2, figsize=(11, 4.4), facecolor=SURFACE)
    for key, label, color in METHODS:
        lat = [d[0] for d in data[key]]
        a1.plot(lat, [d[1] for d in data[key]], color=color, lw=2,
                marker="o", ms=7, mec=SURFACE, mew=2, label=label)
        a2.plot(lat, [d[2] for d in data[key]], color=color, lw=2,
                marker="o", ms=7, mec=SURFACE, mew=2)
    style(a1, f"Position error vs. server ({loss}% loss)", "Mean error (cm, log)")
    a2.axhline(SERVER_ACC, color=TEXT_2, lw=1, ls="--")
    a2.text(300, SERVER_ACC * 1.06, "server's own motion", color=TEXT_2,
            fontsize=8, ha="right", va="bottom")
    a2.text(300, 1250, "Original and Interp 0.7 s overlap", color=TEXT_2,
            fontsize=8, ha="right", va="bottom")
    style(a2, "Motion smoothness (lower is smoother)",
          "Mean |acceleration| (cm/s², log)")
    fig.legend(loc="lower center", ncol=5, frameon=False, fontsize=9,
               labelcolor=TEXT)
    fig.text(0.01, 0.005, "Offline replay, 10 seeds x 60 s per point.",
             color=TEXT_2, fontsize=8)
    fig.tight_layout(rect=(0, 0.08, 1, 1))
    out = os.path.join(HERE, "results", "error_vs_latency.png")
    fig.savefig(out, dpi=150, facecolor=SURFACE)
    print(out)


if __name__ == "__main__":
    main()
