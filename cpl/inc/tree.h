// tree library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef TREE_H_
#define TREE_H_

#include "xcore.h"

#include <numeric>
#include <vector>

CPL_BEGIN

template <class Ty>
class DisjointSet {
public:
    DisjointSet(const std::size_t size) {
        parent.resize(size);
        rank.resize(size, 0);

        std::iota(parent.begin(), parent.end(), 0);
    }

    Ty find(Ty x) {
        auto root = x;
        while (root != parent[root]) {
            root = parent[root];
        }

        while (root != parent[x]) {
            auto next = parent[x];
            parent[x] = root;
            x = next;
        }

        return root;
    }

    void union_rank(Ty x, Ty y) {
        x = find(x);
        y = find(y);

        if (x != y) {
            if (rank[x] < rank[y]) {
                std::swap(x, y);
            }

            parent[y] = x;
            if (rank[x] == rank[y]) {
                ++rank[x];
            }
        }
    }

private:
    std::vector<Ty>          parent;
    std::vector<std::size_t> rank;
};

CPL_END

#endif // TREE_H_
