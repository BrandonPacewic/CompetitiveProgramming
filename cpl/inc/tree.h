// tree / graph library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef TREE_H_
#define TREE_H_

#include "xcore.h"

#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

CPL_BEGIN
template <class MyDisj>
class disjoint_set_const_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using iterator_concept  = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;

private:
    using parent_value_type = typename MyDisj::value_type;
    using parent_rank_type  = typename MyDisj::rank_type;

    using parent_iterator = typename std::vector<parent_value_type>::const_iterator;
    using rank_iterator   = typename std::vector<parent_rank_type>::const_iterator;

protected:
    using pair_cref = std::pair<const parent_value_type&, const parent_rank_type&>;

    struct arrow_proxy {
        pair_cref ref;

        const pair_cref* operator->() const noexcept {
            return &ref;
        }
    };

public:
    using value_type      = std::pair<parent_value_type, parent_rank_type>;
    using reference       = value_type;
    using const_reference = value_type;
    using pointer         = const value_type*;
    using const_pointer   = const value_type*;

    disjoint_set_const_iterator() = default;

    disjoint_set_const_iterator(parent_iterator parent, rank_iterator rank) noexcept : parent(parent), rank(rank) {}

    [[nodiscard]] reference operator*() const noexcept {
        return reference{*parent, *rank};
    }

    [[nodiscard]] arrow_proxy operator->() const noexcept {
        return arrow_proxy{reference{*parent, *rank}};
    }

    disjoint_set_const_iterator& operator++() noexcept {
        ++parent;
        ++rank;
        return *this;
    }

    disjoint_set_const_iterator operator++(int) noexcept {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    disjoint_set_const_iterator& operator--() noexcept {
        --parent;
        --rank;
        return *this;
    }

    disjoint_set_const_iterator operator--(int) noexcept {
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    [[nodiscard]] disjoint_set_const_iterator& operator+=(const difference_type off) noexcept {
        parent += off;
        rank += off;
        return *this;
    }

    [[nodiscard]] disjoint_set_const_iterator operator+(const difference_type off) const noexcept {
        auto tmp = *this;
        tmp += off;
        return tmp;
    }

    [[nodiscard]] friend disjoint_set_const_iterator operator+(
        const difference_type off, disjoint_set_const_iterator next) noexcept {
        next += off;
        return next;
    }

    [[nodiscard]] disjoint_set_const_iterator& operator-=(const difference_type off) noexcept {
        return *this += -off;
    }

    [[nodiscard]] disjoint_set_const_iterator operator-(const difference_type off) const noexcept {
        auto tmp = *this;
        tmp -= off;
        return tmp;
    }

    [[nodiscard]] difference_type operator-(const disjoint_set_const_iterator& right) const noexcept {
        return static_cast<difference_type>(parent - right.parent);
    }

    [[nodiscard]] reference operator[](const difference_type off) const noexcept {
        return *(*this + off);
    }

    [[nodiscard]] bool operator==(const disjoint_set_const_iterator& right) const noexcept {
        return parent == right.parent;
    }

    [[nodiscard]] bool operator!=(const disjoint_set_const_iterator& right) const noexcept {
        return !(*this == right);
    }

    [[nodiscard]] bool operator<(const disjoint_set_const_iterator& right) const noexcept {
        return parent < right.parent;
    }

    [[nodiscard]] bool operator>(const disjoint_set_const_iterator& right) const noexcept {
        return right < *this;
    }

    [[nodiscard]] bool operator<=(const disjoint_set_const_iterator& right) const noexcept {
        return !(right < *this);
    }

    [[nodiscard]] bool operator>=(const disjoint_set_const_iterator& right) const noexcept {
        return !(*this < right);
    }

protected:
    parent_iterator parent;
    rank_iterator   rank;
};

template <class Mydisj>
class disjoint_set_iterator : public disjoint_set_const_iterator<Mydisj> {
protected:
    using Mybase = disjoint_set_const_iterator<Mydisj>;

public:
    using iterator_category = std::random_access_iterator_tag;
    using iterator_concept  = std::random_access_iterator_tag;
    using difference_type   = typename Mybase::difference_type;

    using value_type = typename Mybase::value_type;
    using reference  = typename Mybase::reference;
    using pointer    = typename Mybase::pointer;

    using Mybase::Mybase;

    [[nodiscard]] reference operator*() const noexcept {
        return Mybase::operator*();
    }

    [[nodiscard]] Mybase::arrow_proxy operator->() const noexcept {
        return Mybase::operator->();
    }

    disjoint_set_iterator& operator++() noexcept {
        Mybase::operator++();
        return *this;
    }

    disjoint_set_iterator operator++(int) noexcept {
        auto tmp = *this;
        Mybase::operator++();
        return tmp;
    }

    disjoint_set_iterator& operator--() noexcept {
        Mybase::operator--();
        return *this;
    }

    disjoint_set_iterator operator--(int) noexcept {
        auto tmp = *this;
        Mybase::operator--();
        return tmp;
    }

    [[nodiscard]] disjoint_set_iterator& operator+=(const difference_type off) noexcept {
        Mybase::operator+=(off);
        return *this;
    }

    [[nodiscard]] disjoint_set_iterator operator+(const difference_type off) const noexcept {
        auto tmp = *this;
        tmp += off;
        return tmp;
    }

    [[nodiscard]] friend disjoint_set_iterator operator+(
        const difference_type off, disjoint_set_iterator next) noexcept {
        next += off;
        return next;
    }

    [[nodiscard]] disjoint_set_iterator& operator-=(const difference_type off) noexcept {
        Mybase::operator-=(off);
        return *this;
    }

    [[nodiscard]] disjoint_set_iterator operator-(const difference_type off) const noexcept {
        auto tmp = *this;
        tmp -= off;
        return tmp;
    }

    [[nodiscard]] difference_type operator-(const disjoint_set_iterator& right) const noexcept {
        return static_cast<difference_type>(this->parent - right.parent);
    }

    [[nodiscard]] reference operator[](const difference_type off) const noexcept {
        return const_cast<reference>(Mybase::operator[](off));
    }
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

#ifdef CPL
    using iterator       = disjoint_set_iterator<DisjointSet<value_type>>;
    using const_iterator = disjoint_set_const_iterator<DisjointSet<value_type>>;

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
#endif // CPL

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

template <class InIt, class OutIt, class Pred = EdgeLess>
OutIt kruskal(const std::size_t n, InIt first, InIt last, OutIt dest, Pred pred = Pred{}) {
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
OutIt dijkstra(const std::size_t n, InIt first, InIt last, OutIt dest, const std::size_t start = 0) {
    std::vector<bool>        visited(n, false);
    std::vector<std::size_t> distances(n, std::numeric_limits<std::size_t>::max());
    distances[start] = 0;
    for (std::size_t i = 0; i < n; ++i) {
        auto min_distance = std::numeric_limits<std::size_t>::max();
        auto min_index    = static_cast<std::size_t>(0);
        for (std::size_t j = 0; j < n; ++j) {
            if (!visited[j] && distances[j] <= min_distance) {
                min_distance = distances[j];
                min_index    = j;
            }
        }

        visited[min_index] = true;
        for (auto it = first; it != last; ++it) {
            if (it->from == min_index && !visited[it->to]
                && distances[min_index] != std::numeric_limits<std::size_t>::max()
                && distances[min_index] + (*it).weight < distances[it->to]) {
                distances[it->to] = distances[min_index] + (*it).weight;
            }
        }
    }

    for (std::size_t i = 0; i < n; ++i) {
        *dest = Edge{start, i, distances[i]};
        ++dest;
    }

    return dest;
}

template <class InIt, class OutIt, class Pr1 = EdgeLess, class Pr2 = EdgeLess>
OutIt boruvka(const std::size_t n, InIt first, InIt last, OutIt dest, Pr1 preferred = Pr1{}, Pr2 tie_break = Pr2{}) {
    DisjointSet<std::size_t> ds(n);
    std::vector<std::size_t> cheapest(n, std::numeric_limits<std::size_t>::max());
    std::vector<std::size_t> cheapest_edge(n, std::numeric_limits<std::size_t>::max());

    std::size_t mst_size = 0;
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
                ds.union_rank(cheapest_edge[i], i);
                *dest = Edge{cheapest_edge[i], i, cheapest[i]};
                ++mst_size;
                ++dest;
            }
        }
    }

    return dest;
}

CPL_END

#endif // TREE_H_
