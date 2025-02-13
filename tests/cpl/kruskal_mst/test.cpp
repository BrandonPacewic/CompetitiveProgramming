// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <cassert>
#include <vector>

#include "minimum_spanning_tree_test_cases.hpp"
#include "tree.h"

int main() {
    using namespace std;
    using namespace cpl;
    {
        auto [input, expected] = small_test_case();
        vector<Edge<>> mst;
        kruskal(9, input.begin(), input.end(), back_inserter(mst));
        assert(mst.size() == 8);
        for (size_t i = 0; i < mst.size(); ++i) {
            assert(mst[i].from == expected[i].from);
            assert(mst[i].to == expected[i].to);
            assert(mst[i].weight == expected[i].weight);
        }
    }
    {
        auto [input, expected] = single_edge_test_case();
        vector<Edge<>> mst;
        kruskal(2, input.begin(), input.end(), back_inserter(mst));
        assert(mst.size() == 1);
        for (size_t i = 0; i < mst.size(); ++i) {
            assert(mst[i].from == expected[i].from);
            assert(mst[i].to == expected[i].to);
            assert(mst[i].weight == expected[i].weight);
        }
    }
    {
        auto [input, expected] = large_test_case();
        vector<Edge<>> mst;
        kruskal(100, input.begin(), input.end(), back_inserter(mst));
        assert(mst.size() == 99);
        for (size_t i = 0; i < mst.size(); ++i) {
            // Since this test case contains duplicate weights we can't rely on the to and from
            // fields as they are not guaranteed to be in the same order as the expected output.
            assert(mst[i].weight == expected[i].weight);
        }
    }
    {
        auto [input, expected] = large_sparse_test_case();
        vector<Edge<>> mst;
        kruskal(1000, input.begin(), input.end(), back_inserter(mst));
        assert(mst.size() == 999);
        for (size_t i = 0; i < mst.size(); ++i) {
            // Since this test case contains duplicate weights we can't rely on the to and from
            // fields as they are not guaranteed to be in the same order as the expected output.
            assert(mst[i].weight == expected[i].weight);
        }
    }

    return 0;
}
