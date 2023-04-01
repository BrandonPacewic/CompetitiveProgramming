// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <container.h>

#include <cassert>

int main() {
    using namespace std;
    using namespace cpl;
    {
        vector<int> input  = {};
        auto        output = to_set(input.begin(), input.end());
        assert(output == set<int>());
    }
    {
        vector<int> input    = {1, 2, 3, 4, 5};
        set<int>    expected = {1, 2, 3, 4, 5};
        auto        output   = to_set(input.begin(), input.end());
        assert(output == expected);
    }
    {
        vector<int>        input    = {};
        unordered_set<int> expected = {};
        auto               output   = to_unordered_set(input.begin(), input.end());
        assert(output == expected);
    }
    {
        vector<int>        input    = {1, 2, 3, 4, 5};
        unordered_set<int> expected = {1, 2, 3, 4, 5};
        auto               output   = to_unordered_set(input.begin(), input.end());
        assert(output == expected);
    }

    return 0;
}