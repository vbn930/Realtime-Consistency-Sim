"""Run the latency x loss grid and write per-run and summary CSV files.

    python3 run_benchmark.py            # full grid, 10 seeds
    python3 run_benchmark.py --seeds 2  # quick check
"""

from __future__ import annotations

import argparse
import csv
import itertools
import os
from concurrent.futures import ProcessPoolExecutor

import numpy as np

import rcsim

LATENCIES = [0.0, 0.05, 0.1, 0.2, 0.3]
LOSSES = [0.0, 0.2, 0.4, 0.6]
# scenarios of Table 1 in Docs/Research_Report.pdf
REPORT_SCENARIOS = [(0.110, 0.20), (0.110, 0.61), (0.304, 0.0), (0.310, 0.40)]
CLEAN_METHODS = ["off", "original", "interp_0.7s", "interp_adaptive", "dr_present"]

# Noisy-state study: snapshot position/velocity carry Gaussian noise.
# Kalman q was chosen on seeds 100-102, which are not used below.
NOISE = (10.0, 60.0)
NOISE_CONDITIONS = [(0.1, 0.2), (0.3, 0.4)]
NOISE_METHODS = [("dr_present", {}),
                 ("kf_present", {"kf_q": 1e5}),
                 ("kf_present", {"kf_q": 1e6})]

METRICS = ["err_mean", "err_rmse", "err_p95", "err_max", "dr_frac",
           "acc_mean", "acc_p99"]


def job(args):
    study, label, method, kw, lat, loss, noise, seed = args
    net = rcsim.NetConfig(latency=lat, loss=loss,
                          pos_noise=noise[0], vel_noise=noise[1])
    if method == "kf_present":
        kw = dict(kw, pos_sigma=max(noise[0], 1.0), vel_sigma=max(noise[1], 5.0))
    m = rcsim.run(method, net, seed, **kw).metrics
    return {"study": study, "method": label, "latency_ms": round(lat * 1000),
            "loss_pct": round(loss * 100), "seed": seed, **m}


def build_jobs(seeds: list[int]):
    jobs = []
    conditions = list(itertools.product(LATENCIES, LOSSES))
    for lat, loss in conditions + REPORT_SCENARIOS:
        study = "grid" if (lat, loss) in conditions else "report"
        for method in CLEAN_METHODS:
            for s in seeds:
                jobs.append((study, method, method, {}, lat, loss, (0.0, 0.0), s))
    for lat, loss in NOISE_CONDITIONS:
        for method, kw in NOISE_METHODS:
            label = method if not kw else f"{method}_q{kw['kf_q']:.0e}"
            for s in seeds:
                jobs.append(("noise", label, method, kw, lat, loss, NOISE, s))
    return jobs


def summarize(rows):
    groups = {}
    for r in rows:
        key = (r["study"], r["method"], r["latency_ms"], r["loss_pct"])
        groups.setdefault(key, []).append(r)
    out = []
    for key, rs in sorted(groups.items()):
        row = dict(zip(["study", "method", "latency_ms", "loss_pct"], key))
        row["runs"] = len(rs)
        for m in METRICS:
            v = np.array([r[m] for r in rs])
            row[m] = round(float(v.mean()), 3)
            row[m + "_sd"] = round(float(v.std(ddof=1)) if len(v) > 1 else 0.0, 3)
        out.append(row)
    return out


def write_csv(path, rows):
    with open(path, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0].keys()))
        w.writeheader()
        w.writerows(rows)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--seeds", type=int, default=10)
    ap.add_argument("--out", default=os.path.join(os.path.dirname(__file__), "results"))
    args = ap.parse_args()
    os.makedirs(args.out, exist_ok=True)
    jobs = build_jobs(list(range(args.seeds)))
    with ProcessPoolExecutor() as ex:
        rows = list(ex.map(job, jobs, chunksize=4))
    write_csv(os.path.join(args.out, "runs.csv"), rows)
    write_csv(os.path.join(args.out, "summary.csv"), summarize(rows))
    print(f"{len(rows)} runs -> {args.out}")


if __name__ == "__main__":
    main()
