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

CPL_END

#endif // TREE_H_
