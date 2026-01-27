// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <cassert>
#include <vector>

#include "minimum_spanning_tree_test_cases.hpp"
#include "tree.h"

template <class EdgeContainer>
auto total_weight(const EdgeContainer& edges) {
    using weight_type = decltype(edges[0].weight);
    weight_type sum   = 0;
    for (const auto& e : edges) {
        sum += e.weight;
    }
    return sum;
}

int main() {
    using namespace std;
    using namespace cpl;

    {
        auto [input, expected] = small_test_case();
        vector<Edge<>> mst;
        boruvka(9, input.begin(), input.end(), back_inserter(mst));

        assert(mst.size() == 8);

        auto expected_weight = total_weight(expected);
        auto actual_weight   = total_weight(mst);
        assert(actual_weight == expected_weight);
    }
    {
        auto [input, expected] = single_edge_test_case();
        vector<Edge<>> mst;
        boruvka(2, input.begin(), input.end(), back_inserter(mst));

        assert(mst.size() == 1);
        assert(total_weight(mst) == total_weight(expected));
    }
    {
        vector<Edge<>> input = {
            {0, 1, 1},
            {1, 2, 2},
            {0, 2, 3},
        };
        vector<Edge<>> mst;
        boruvka(3, input.begin(), input.end(), back_inserter(mst));

        assert(mst.size() == 2);
        assert(total_weight(mst) == 3);
    }
    {
        auto [input, expected] = same_weight_test_case();
        vector<Edge<>> mst;
        boruvka(4, input.begin(), input.end(), back_inserter(mst));

        assert(mst.size() == 3);
        assert(total_weight(mst) == total_weight(expected));
    }
    {
        auto [input, expected] = large_test_case();
        vector<Edge<>> mst;
        boruvka(100, input.begin(), input.end(), back_inserter(mst));

        assert(mst.size() == 99);
        assert(total_weight(mst) == total_weight(expected));
    }
    {
        auto [input, expected] = large_sparse_test_case();
        vector<Edge<>> mst;
        boruvka(1000, input.begin(), input.end(), back_inserter(mst));

        assert(mst.size() == 999);
        assert(total_weight(mst) == total_weight(expected));
    }

    return 0;
}
