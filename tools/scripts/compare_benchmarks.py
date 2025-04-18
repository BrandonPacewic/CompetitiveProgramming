# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

import os
import re
import subprocess
from pathlib import Path
from collections import defaultdict

BUILD_DIR = "build"
RESULTS_DIR = Path(BUILD_DIR) / "benchmarks" / "results"
GOOGLE_BENCHMARK_COMPARE_SCRIPT = Path("../../../benchmarks/benchmark/tools/compare.py")


def extract_algo_name(filename: str) -> str:
    # Removes timestamp and UUID prefix
    # Matches: 2025-04-17_13-23-38_abcdef_algo.json
    return re.sub(r"^[0-9]{4}-[0-9]{2}-[0-9]{2}_[^_]+_[^_]+_", "", filename)


def main() -> None:
    print("Comparing most recent benchmarks per algorithm...")

    if not RESULTS_DIR.is_dir():
        print(f"Results directory '{RESULTS_DIR}' not found.")
        return

    algo_files = defaultdict(list)
    for file in sorted(RESULTS_DIR.glob("*.json"), key=os.path.getmtime, reverse=True):
        algo = extract_algo_name(file.name)
        algo_files[algo].append(file)

    for algo, files in algo_files.items():
        if len(files) < 2:
            print(f"Skipping {algo} (need at least 2 versions)")
            continue

        new, old = files[:2]
        name = algo.replace(".json", "").replace(".cpp", "")

        print("────────────────────────────────────────────────────────────")
        print(f"Algorithm: {name}")
        print("Comparing most recent two runs:")
        print(f"   OLD: {old.name}")
        print(f"   NEW: {new.name}\n")

        try:
            subprocess.run(
                ["python", str(GOOGLE_BENCHMARK_COMPARE_SCRIPT), "benchmarks", old.name, new.name],
                cwd=RESULTS_DIR,
                check=False,
            )
        except Exception as e:
            print(f"Error running compare script: {e}")
        print()


if __name__ == "__main__":
    main()
