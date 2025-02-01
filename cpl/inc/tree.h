// tree / graph library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef TREE_H_
#define TREE_H_

#include "xcore.h"

#include <numeric>
#include <vector>

CPL_BEGIN
template <class MyDisj>
class _Disjoint_set_const_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;

protected:
    using parent_iterator = typename std::vector<typename MyDisj::value_type>::iterator;
    using rank_iterator   = typename std::vector<typename MyDisj::rank_type>::iterator;

public:
    using value_type      = std::pair<typename MyDisj::value_type, typename MyDisj::rank_type>;
    using difference_type = std::ptrdiff_t;
    using pointer         = value_type*;
    using const_pointer   = value_type*;
    using reference       = value_type&;
    using const_reference = const value_type&;

    _Disjoint_set_const_iterator(parent_iterator parent, rank_iterator rank) noexcept : parent(parent), rank(rank) {}

    [[nodiscard]] value_type operator*() const noexcept {
        return {(*parent), (*rank)};
    }

    [[nodiscard]] pointer operator->() const noexcept {
        return &operator*();
    }

    _Disjoint_set_const_iterator& operator++() noexcept {
        ++parent;
        ++rank;
        return *this;
    }

    _Disjoint_set_const_iterator& operator++(int) noexcept {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    _Disjoint_set_const_iterator& operator--() noexcept {
        --parent;
        --rank;
        return *this;
    }

    _Disjoint_set_const_iterator& operator--(int) noexcept {
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    [[nodiscard]] _Disjoint_set_const_iterator& operator+=(const difference_type off) noexcept {
        parent += off;
        rank += off;
        return *this;
    }

    [[nodiscard]] _Disjoint_set_const_iterator operator+(const difference_type off) const noexcept {
        auto tmp = *this;
        tmp += off;
        return tmp;
    }

    [[nodiscard]] friend _Disjoint_set_const_iterator operator+(
        const difference_type off, _Disjoint_set_const_iterator next) noexcept {
        next += off;
        return next;
    }

    [[nodiscard]] _Disjoint_set_const_iterator& operator-=(const difference_type off) noexcept {
        return *this += -off;
    }

    [[nodiscard]] _Disjoint_set_const_iterator operator-(const difference_type off) const noexcept {
        auto tmp = *this;
        tmp -= off;
        return tmp;
    }

    [[nodiscard]] difference_type operator-(const _Disjoint_set_const_iterator& right) const noexcept {
        return static_cast<difference_type>(parent - right.parent);
    }

    [[nodiscard]] bool operator==(const _Disjoint_set_const_iterator& right) const noexcept {
        return parent == right.parent;
    }

    [[nodiscard]] bool operator!=(const _Disjoint_set_const_iterator& right) const noexcept {
        return !(*this == right);
    }

protected:
    parent_iterator parent;
    rank_iterator   rank;
};

template <class Mydisj>
class _Disjoint_set_iterator : public _Disjoint_set_const_iterator<Mydisj> {
protected:
    using _Mybase = _Disjoint_set_const_iterator<Mydisj>;

public:
    using _Mybase::_Mybase;
};

template <class Ty, class Ranty = std::size_t>
class DisjointSet { // fixed size union find structure
public:
    using value_type = Ty;
    using rank_type  = Ranty;

    DisjointSet() = default;

    explicit DisjointSet(const std::size_t size) {
        this->resize(size);
    }

    DisjointSet(const DisjointSet&)     = default;
    DisjointSet(DisjointSet&&) noexcept = default;

    DisjointSet& operator=(const DisjointSet&)     = default;
    DisjointSet& operator=(DisjointSet&&) noexcept = default;

    [[nodiscard]] Ty find(Ty x) {
        auto root = x;
        while (root != parent[root]) {
            root = parent[root];
        }

        while (root != parent[x]) {
            auto next = parent[x];
            parent[x] = root;
            x         = next;
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

    [[nodiscard]] std::size_t size() const {
        return parent.size();
    }

    void resize(const std::size_t size) {
        parent.resize(size);
        std::iota(parent.begin(), parent.end(), 0);

        rank.resize(size, 0);
    }

    using iterator       = _Disjoint_set_iterator<DisjointSet<value_type>>;
    using const_iterator = _Disjoint_set_const_iterator<DisjointSet<value_type>>;

    [[nodiscard]] iterator begin() noexcept {
        return iterator(parent.begin(), rank.begin());
    }

    [[nodiscard]] const_iterator begin() const noexcept {
        return const_iterator(parent.begin(), rank.begin());
    }

    [[nodiscard]] iterator end() noexcept {
        return iterator(parent.end(), rank.end());
    }

    [[nodiscard]] const_iterator end() const noexcept {
        return const_iterator(parent.end(), rank.end());
    }

private:
    std::vector<value_type> parent;
    std::vector<rank_type>  rank;
};

template <class Valty = std::size_t>
struct Edge {
    Valty from;
    Valty to;
    Valty weight;
};

struct EdgeLess {
    template <class Ed1, class Ed2>
        requires requires(Ed1&& left, Ed2&& right) {
            { std::forward<Ed1>(left).weight < std::forward<Ed2>(right).weight } -> std::convertible_to<bool>;
        }
    [[nodiscard]] constexpr bool operator()(Ed1&& left, Ed2&& right) const
        noexcept(noexcept(std::forward<Ed1>(left).weight < std::forward<Ed2>(right).weight)) {
        return std::forward<Ed1>(left).weight < std::forward<Ed2>(right).weight;
    }

    using is_transparent = int;
};

struct EdgeGreater {
    template <class Ed1, class Ed2>
        requires requires(Ed1&& left, Ed2&& right) {
            { std::forward<Ed1>(left).weight > std::forward<Ed2>(right).weight } -> std::convertible_to<bool>;
        }
    [[nodiscard]] constexpr bool operator()(Ed1&& left, Ed2&& right) const
        noexcept(noexcept(std::forward<Ed1>(left).weight > std::forward<Ed2>(right).weight)) {
        return std::forward<Ed1>(left).weight > std::forward<Ed2>(right).weight;
    }

    using is_transparent = int;
};

template <class InIt, class OutIt, class Pred>
OutIt kruskal(const std::size_t num_nodes, InIt first, InIt last, OutIt dest, Pred pred) {
    DisjointSet<std::size_t> ds(num_nodes);
    std::sort(first, last, pred);
    std::size_t edge_count = 0;
    for (auto it = first; it != last; ++it) {
        if (ds.find(it->from) != ds.find(it->to)) {
            *dest = *it;
            ++dest;
            ds.union_rank(it->from, it->to);

            if (++edge_count == num_nodes - 1) {
                break;
            }
        }
    }

    return dest;
}

template <class InIt, class OutIt>
OutIt kruskal(const std::size_t num_nodes, InIt first, InIt last, OutIt dest) {
    return kruskal(num_nodes, first, last, dest, EdgeLess{});
}

std::vector<Edge> dijkstra(const std::size_t num_nodes, const std::vector<Edge>& edges, const std::size_t start) {
    std::vector<Edge>        shortest_paths;
    std::vector<bool>        visited(num_nodes, false);
    std::vector<std::size_t> distances(num_nodes, std::numeric_limits<std::size_t>::max());

    distances[start] = 0;

    for (std::size_t i = 0; i < num_nodes; ++i) {
        std::size_t min_distance = std::numeric_limits<std::size_t>::max();
        std::size_t min_index    = 0;

        for (std::size_t j = 0; j < num_nodes; ++j) {
            if (!visited[j] && distances[j] <= min_distance) {
                min_distance = distances[j];
                min_index    = j;
            }
        }

        visited[min_index] = true;

        for (const auto& edge : edges) {
            if (edge.from == min_index && !visited[edge.to]
                && distances[min_index] != std::numeric_limits<std::size_t>::max()
                && distances[min_index] + edge.weight < distances[edge.to]) {
                distances[edge.to] = distances[min_index] + edge.weight;
            }
        }
    }

    for (std::size_t i = 0; i < num_nodes; ++i) {
        shortest_paths.push_back({start, i, distances[i]});
    }

    return shortest_paths;
}

template <class InIt, class OutIt, class Pr1, class Pr2>
OutIt boruvka(const std::size_t num_nodes, InIt first, InIt last, OutIt dest, Pr1 is_preferred_over, Pr2 tie_break) {
    std::vector<Edge>        mst;
    DisjointSet<std::size_t> ds(num_nodes);

    std::vector<std::size_t> cheapest(num_nodes, std::numeric_limits<std::size_t>::max());
    std::vector<std::size_t> cheapest_edge(num_nodes, std::numeric_limits<std::size_t>::max());

    while (mst.size() < num_nodes - 1) {
        for (std::size_t i = 0; i < num_nodes; ++i) {
            cheapest[i]      = std::numeric_limits<std::size_t>::max();
            cheapest_edge[i] = std::numeric_limits<std::size_t>::max();
        }

        for (auto it = first; it != last; ++it) {
            auto set1 = ds.find(it->from);
            auto set2 = ds.find(it->to);

            if (set1 == set2) {
                continue;
            }

            if (is_preferred_over(it->weight, cheapest[set1])
                || (it->weight == cheapest[set1] && tie_break(it->weight, cheapest_edge[set1]))) {
                cheapest[set1]      = it->weight;
                cheapest_edge[set1] = it->to;
            }

            if (is_preferred_over(it->weight, cheapest[set2])
                || (it->weight == cheapest[set2] && tie_break(it->weight, cheapest_edge[set2]))) {
                cheapest[set2]      = it->weight;
                cheapest_edge[set2] = it->from;
            }
        }

        for (std::size_t i = 0; i < num_nodes; ++i) {
            if (cheapest[i] != std::numeric_limits<std::size_t>::max()) {
                *dest = Edge{cheapest_edge[i], i, cheapest[i]};
                ++dest;
                ds.union_rank(cheapest_edge[i], i);
            }
        }
    }

    return dest;
}

template <class InIt, class OutIt>
OutIt boruvka(const std::size_t num_nodes, InIt first, InIt last, OutIt dest) {
    return boruvka(
        num_nodes, first, last, dest, [](const auto& a, const auto& b) { return a < b; },
        [](const auto& a, const auto& b) { return a < b; });
}

CPL_END

#endif // TREE_H_
