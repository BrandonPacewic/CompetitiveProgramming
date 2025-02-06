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
#ifdef USE_DISJOINT_SET_ITERATORS
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
#endif // USE_DISJOINT_SET_ITERATORS

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

#ifdef USE_DISJOINT_SET_ITERATORS
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
#endif // USE_DISJOINT_SET_ITERATORS

private:
    std::vector<value_type> parent;
    std::vector<rank_type>  rank;
};

template <class Ty = std::size_t>
struct Edge {
    Ty from;
    Ty to;
    Ty weight;
};

template <typename T>
concept HasWeight = requires(T t) {
    { t.weight } -> std::convertible_to<std::size_t>;
};

class EdgeComparatorBase {
protected:
    template <class Ty>
        requires HasWeight<std::remove_cvref_t<Ty>>
    [[nodiscard]] static constexpr auto get_weight(Ty&& edge) noexcept -> decltype(std::forward<Ty>(edge).weight) {
        return std::forward<Ty>(edge).weight;
    }

    template <class Ty>
        requires (!HasWeight<std::remove_cvref_t<Ty>>)
    [[nodiscard]] static constexpr Ty&& get_weight(Ty&& edge) noexcept {
        return std::forward<Ty>(edge);
    }
};

class EdgeLess : private EdgeComparatorBase {
public:
    template <class Lhs, class Rhs>
        requires requires(Lhs&& left, Rhs&& right) {
            { get_weight(std::forward<Lhs>(left)) < get_weight(std::forward<Rhs>(right)) } -> std::convertible_to<bool>;
        }
    [[nodiscard]] constexpr bool operator()(Lhs&& left, Rhs&& right) const
        noexcept(noexcept(get_weight(std::forward<Lhs>(left)) < get_weight(std::forward<Rhs>(right)))) {
        return get_weight(std::forward<Lhs>(left)) < get_weight(std::forward<Rhs>(right));
    }

    using is_transparent = int;
};

class EdgeGreater : private EdgeComparatorBase {
public:
    template <class Lhs, class Rhs>
        requires requires(Lhs&& left, Rhs&& right) {
            { get_weight(std::forward<Lhs>(left)) > get_weight(std::forward<Rhs>(right)) } -> std::convertible_to<bool>;
        }
    [[nodiscard]] constexpr bool operator()(Lhs&& left, Rhs&& right) const
        noexcept(noexcept(get_weight(std::forward<Lhs>(left)) > get_weight(std::forward<Rhs>(right)))) {
        return get_weight(std::forward<Lhs>(left)) > get_weight(std::forward<Rhs>(right));
    }

    using is_transparent = int;
};

template <class InIt, class OutIt, class Pred>
OutIt kruskal(const std::size_t n, InIt first, InIt last, OutIt dest, Pred pred) {
    DisjointSet<std::size_t> ds(n);
    std::sort(first, last, pred);
    std::size_t edge_count = 0;
    for (auto it = first; it != last; ++it) {
        if (ds.find(it->from) != ds.find(it->to)) {
            *dest = *it;
            ++dest;
            ds.union_rank(it->from, it->to);

            ++edge_count;
            if (edge_count == n - 1) {
                break;
            }
        }
    }

    return dest;
}

template <class InIt, class OutIt>
OutIt kruskal(const std::size_t n, InIt first, InIt last, OutIt dest) {
    return kruskal(n, first, last, dest, EdgeLess{});
}

template <class InIt, class OutIt>
OutIt dijkstra(const std::size_t n, InIt first, InIt last, OutIt dest, const std::size_t start) {
    std::vector<bool>        visited(n, false);
    std::vector<std::size_t> distances(n, std::numeric_limits<std::size_t>::max());
    distances[start] = 0;
    for (std::size_t i = 0; i < n; ++i) {
        auto        min_distance = std::numeric_limits<std::size_t>::max();
        std::size_t min_i        = 0;
        for (std::size_t j = 0; j < n; ++j) {
            if (!visited[j] && distances[j] <= min_distance) {
                min_distance = distances[j];
                min_i        = j;
            }
        }

        visited[min_i] = true;
        for (auto it = first; it != last; ++it) {
            if (it->from == min_i && !visited[it->to] && distances[min_i] != std::numeric_limits<std::size_t>::max()
                && distances[min_i] + (*it).weight < distances[it->to]) {
                distances[it->to] = distances[min_i] + (*it).weight;
            }
        }
    }

    for (std::size_t i = 0; i < n; ++i) {
        *dest = Edge{start, i, distances[i]};
        ++dest;
    }

    return dest;
}

template <class InIt, class OutIt>
OutIt dijkstra(const std::size_t n, InIt first, InIt last, OutIt dest) {
    return dijkstra(n, first, last, dest, 0);
}

template <class InIt, class OutIt, class Pr1, class Pr2>
OutIt boruvka(const std::size_t n, InIt first, InIt last, OutIt dest, Pr1 preferred, Pr2 tie_break) {
    std::size_t              mst_size = 0;
    DisjointSet<std::size_t> ds(n);
    std::vector<std::size_t> cheapest(n, std::numeric_limits<std::size_t>::max());
    std::vector<std::size_t> cheapest_edge(n, std::numeric_limits<std::size_t>::max());

    while (mst_size < n - 1) {
        for (std::size_t i = 0; i < n; ++i) {
            cheapest[i]      = std::numeric_limits<std::size_t>::max();
            cheapest_edge[i] = std::numeric_limits<std::size_t>::max();
        }

        for (auto it = first; it != last; ++it) {
            auto set1 = ds.find(it->from);
            auto set2 = ds.find(it->to);

            if (set1 == set2) {
                continue;
            }

            if (preferred(*it, cheapest[set1]) || (tie_break(*it, cheapest[set1]) && it->weight == cheapest[set1])) {
                cheapest[set1]      = it->weight;
                cheapest_edge[set1] = it->to;
            }
        }

        for (std::size_t i = 0; i < n; ++i) {
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
OutIt boruvka(const std::size_t n, InIt first, InIt last, OutIt dest) {
    return boruvka(n, first, last, dest, EdgeLess{}, EdgeLess{});
}

CPL_END

#endif // TREE_H_
