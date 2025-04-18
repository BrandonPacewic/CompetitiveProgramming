# Copyright (c) Brandon Pacewic
# SPDX-License-Identifier: MIT

import os
import re
import json
from pathlib import Path
from collections import defaultdict

BUILD_DIR = "build"
RESULTS_DIR = Path(BUILD_DIR) / "benchmarks" / "results"


def extract_algo_name(filename: str) -> str:
    # Removes timestamp and UUID prefix
    # Matches: 2025-04-17_13-23-38_abcdef_algo.json
    return re.sub(r"^[0-9]{4}-[0-9]{2}-[0-9]{2}_[^_]+_[^_]+_", "", filename)


def print_benchmark_data(file_path: Path) -> None:
    try:
        with open(file_path, 'r') as f:
            data = json.load(f)

        for bench in data.get("benchmarks", []):
            name = bench.get("name", "")
            real_time = bench.get("real_time", 0.0)
            cpu_time = bench.get("cpu_time", 0.0)
            iterations = bench.get("iterations", 0)
            print(f"{name:<30}  Time: {real_time:>10.2f}  CPU: {cpu_time:>10.2f}  Iter: {iterations}")
    except Exception as e:
        print(f"Error reading {file_path.name}: {e}")


def main() -> None:
    print("Showing most recent benchmark outputs per algorithm...")
    if not RESULTS_DIR.is_dir():
        print(f"Results directory '{RESULTS_DIR}' not found.")
        return

    algo_to_files = defaultdict(list)
    for file in sorted(RESULTS_DIR.glob("*.json"), key=os.path.getmtime, reverse=True):
        algo_name = extract_algo_name(file.name)
        algo_to_files[algo_name].append(file)

    for algo, files in algo_to_files.items():
        latest = files[0]
        display_name = algo.replace(".json", "").replace(".cpp", "")

        print("────────────────────────────────────────────────────────────")
        print(f"Algorithm: {display_name}")
        print(f"File: {latest.name}\n")

        print_benchmark_data(latest)
        print()


if __name__ == "__main__":
    main()
