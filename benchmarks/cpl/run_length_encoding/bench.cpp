// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <benchmark/benchmark.h>
#include <algorithm>
#include <vector>
#include <cstdint>
#include <random>

#include "container.h"

using namespace std;
using namespace cpl;

template <class T>
void bench(benchmark::State& state) {
    mt19937 gen(96337);

    const size_t size = static_cast<size_t>(state.range(0));

    vector<T> input(size);

    uniform_int_distribution<T> dist(numeric_limits<T>::min(), numeric_limits<T>::max());
    ranges::generate(input, [&] { return dist(gen); });

    for (auto _ : state) {
        benchmark::DoNotOptimize(input);
        benchmark::DoNotOptimize(run_length_encoding(input.begin(), input.end()));
    }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
BENCHMARK(bench<int8_t>)->Range(8, 8<<10);
BENCHMARK(bench<int16_t>)->Range(8, 8<<10);
BENCHMARK(bench<int32_t>)->Range(8, 8<<10);
BENCHMARK(bench<int64_t>)->Range(8, 8<<10);
#pragma GCC diagnostic pop

BENCHMARK_MAIN();
