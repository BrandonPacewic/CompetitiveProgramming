// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <container.h>

#include <cassert>

int main() {
    using namespace std;
    using namespace cpl;
    {
        vector<int> input{};
        vector<pair<int, uint16_t>> expected{};
        const auto output = run_length_encoding(input.begin(), input.end());
        assert(output == expected);
    }
    {
        vector<int> input = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
        vector<pair<int, uint16_t>> expected = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
        const auto output = run_length_encoding(input.begin(), input.end());
        assert(output == expected);
    }

    return 0;
}