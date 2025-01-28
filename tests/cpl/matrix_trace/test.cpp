// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <matrix.h>

#include <cassert>
#include <vector>

int main() {
    using namespace std;
    using namespace cpl;
    {
        // clang-format off
        vector<vector<int>> v{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        // clang-format on

        uint8_t trace = matrix_trace(v.begin(), v.end());
        assert(trace == 15);
    }
    {
        vector<vector<int>> v{};
        uint8_t             trace = matrix_trace(v.begin(), v.end());
        assert(trace == 0);
    }

    return 0;
}
