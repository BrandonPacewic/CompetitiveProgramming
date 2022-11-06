// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <matrix.h>

#include <cassert>
#include <vector>

int main() {
    using namespace std;
    using namespace cpl;

    vector<vector<int>> v{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    {
        // Normal trace; top left to bottom right.
        uint8_t trace = matrix_trace(v.begin(), v.end());
        assert(trace == 15);
    }
    {
        // Reverse trace; bottom left to top right.
        uint8_t trace = matrix_trace(v.begin(), v.end(), true);
        assert(trace == 15);
    }

    return 0;
}
