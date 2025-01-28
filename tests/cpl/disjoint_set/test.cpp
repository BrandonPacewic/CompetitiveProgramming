// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <cassert>
#include <iostream>

#include "tree.h"

int main() {
    using namespace std;
    using namespace cpl;
    {
        DisjointSet<int> ds(10);
        for (int i = 0; i < 10; ++i) {
            assert(ds.find(i) == i);
        }
    }
    {
        DisjointSet<int> ds(10);
        ds.union_rank(1, 2);
        assert(ds.find(1) == ds.find(2));

        ds.union_rank(3, 4);
        ds.union_rank(2, 3);
        assert(ds.find(1) == ds.find(4));
    }
    {
        DisjointSet<int> ds_single(1);
        assert(ds_single.find(0) == 0);

        DisjointSet<int> ds(5);
        ds.union_rank(0, 1);
        ds.union_rank(1, 2);
        assert(ds.find(0) == ds.find(2));
        ds.union_rank(0, 2);
        assert(ds.find(0) == ds.find(2));
    }
    {
        DisjointSet<int> ds(6);
        for (int i = 0; i < 5; ++i) {
            ds.union_rank(i, i + 1);
        }

        for (int i = 0; i < 6; ++i) {
            assert(ds.find(i) == 0);
        }
    }
    {
        DisjointSet<int> ds(5);
        ds.union_rank(0, 1);
        ds.union_rank(1, 2);
        ds.union_rank(3, 4);
        vector<pair<int, size_t>> expected = {{0, 1}, {0, 0}, {0, 0}, {3, 1}, {3, 0}};
        size_t                    index    = 0;

        for (const auto& [parent, rank] : ds) {
            assert(parent == expected[index].first);
            assert(rank == expected[index].second);
            ++index;
        }

        assert(index == ds.size());
    }

    return 0;
}
