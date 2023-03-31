// matrix library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef MATRIX_H_
#define MATRIX_H_
#include <core.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>

CPL_BEGIN

template <typename Ty, std::size_t N>
class basic_uniform_matrix {
public:
    using value_type = Ty;
    using row_type = std::array<Ty, N>;
    using pointer = row_type*;
    using const_pointer = const row_type*;
    using reference = row_type&;
    using const_reference = const row_type&;
    using size_type = std::size_t;

    basic_uniform_matrix() = default;

    basic_uniform_matrix(const basic_uniform_matrix&) = default;

    basic_uniform_matrix(basic_uniform_matrix&&) noexcept = default;

    basic_uniform_matrix& operator=(const basic_uniform_matrix&) = default;

    basic_uniform_matrix& operator=(basic_uniform_matrix&&) = default;

    reference operator[](size_type index) {
        return rows[index];
    }

    const_reference operator[](size_type index) const {
        return rows[index];
    }

    // The number of rows and cols are the same.
    constexpr size_type size() const {
        return N;
    }

    constexpr pointer begin() {
        return rows.begin();
    }

    constexpr const_pointer begin() const {
        return rows.begin();
    }

    constexpr pointer end() {
        return rows.end();
    }

    constexpr const_pointer end() const {
        return rows.end();
    }

    reference front() {
        return rows.front();
    }

    const_reference front() const {
        return rows.front();
    }

    reference back() {
        return rows.back();
    }

    const_reference back() const {
        return rows.back();
    }

private:
    std::array<std::array<Ty, N>, N> rows;
};

template <typename T_matrix>
const void output_matrix(const T_matrix& matrix, const bool& space = true, const bool& new_line = true) {
    for (std::size_t row = 0; row < matrix.size(); ++row) {
        for (std::size_t col = 0; col < matrix[row].size(); ++col) {
            std::cout << matrix[row][col];

            if (space && col < matrix[row].size() - 1) {
                std::cout << ' ';
            }
        }

        std::cout << (new_line ? '\n' : ' ');
    }
}

template <typename T_matrix>
const void output_reverse_matrix(const T_matrix& matrix, const bool& space = true, const bool& new_line = true) {
    for (std::size_t row = matrix.size(); row > 0; --row) {
        for (std::size_t col = matrix[row - 1].size(); col > 0; --col) {
            std::cout << matrix[row - 1][col - 1];

            if (space && col > 1) {
                std::cout << ' ';
            }
        }

        std::cout << (new_line ? '\n' : ' ');
    }
}

const void output_empty_matrix(const uint16_t& rows, const uint16_t& cols, const char& primary, const char& secondary,
                               std::function<bool(uint16_t&, uint16_t&)> evaluation, const bool& space = false);

template <typename ForwardIterator, typename UnaryPredicate>
[[nodiscard]] const bool matrix_any_of(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
    for (; first != last; ++first) {
        if (std::any_of((*first).begin(), (*first).end(), pred)) {
            return true;
        }
    }

    return false;
}

template <typename ForwardIterator, typename UnaryPredicate>
[[nodiscard]] const bool matrix_all_of(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
    for (; first != last; ++first) {
        if (!std::all_of((*first).begin(), (*first).end(), pred)) {
            return false;
        }
    }

    return true;
}

template <typename ForwardIterator, typename UnaryPredicate>
[[nodiscard]] const bool matrix_none_of(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
    for (; first != last; ++first) {
        if (!std::none_of((*first).begin(), (*first).end(), pred)) {
            return false;
        }
    }

    return true;
}

template <typename ForwardIterator, typename ValueType>
void matrix_fill(ForwardIterator first, ForwardIterator last, const ValueType& value) {
    for (; first != last; ++first) {
        std::fill((*first).begin(), (*first).end(), value);
    }
}

template <typename ForwardIterator, typename ValueType>
[[nodiscard]] const ForwardIterator matrix_find(ForwardIterator first, ForwardIterator last, const ValueType& value) {
    for (; first != last; ++first) {
        const auto it = std::find((*first).begin(), (*first).end(), value);

        if (it != (*first).end()) {
            return it;
        }
    }

    return last.end();
}

template <typename ForwardIterator, typename UnaryPredicate>
[[nodiscard]] const ForwardIterator matrix_find_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
    for (; first != last; ++first) {
        const auto it = std::find_if((*first).begin(), (*first).end(), pred);

        if (it != (*first).end()) {
            return it;
        }
    }

    return last;
}

template <typename ForwardIterator, typename UnaryFunction>
UnaryFunction matrix_for_each(ForwardIterator first, ForwardIterator last, UnaryFunction func) {
    for (; first != last; ++first) {
        std::for_each((*first).begin(), (*first).end(), func);
    }

    return func;
}

template <typename ForwardIterator, typename LinearContainer>
void fill_from_linear_container(ForwardIterator first, ForwardIterator last, const LinearContainer& container) {
    std::size_t linear_index = 0;

    for_each(first, last, [&](auto& cell) { cell = container[linear_index], ++linear_index; });
}

template <typename ForwardIterator, typename ValueType>
void matrix_iota(ForwardIterator first, ForwardIterator last, ValueType value) {
    for (; first != last; ++first) {
        for (auto itr = (*first).begin(); itr != (*first).end(); ++itr) {
            *itr = value;
            ++value;
        }
    }
}

template <typename ForwardIterator, typename ValueType, typename ReturnContainerType = std::vector<ValueType>>
[[nodiscard]] ReturnContainerType create_linear_sequence(ForwardIterator first, ForwardIterator last) {
    // TODO: Vector is needed for an undefined matrix but other containers can
    // Be used for a %basic_uniform_matrix type
    ReturnContainerType sequence;

    for (; first != last; ++first) {
        for (auto itr = (*first).begin(); itr != (*first).end(); ++itr) {
            sequence.push_back(*itr);
        }
    }

    return sequence;
}

template <typename ForwardIterator, typename BinaryPredicate>
[[nodiscard]] const bool matrix_is_sorted(ForwardIterator first, ForwardIterator last,
                                          BinaryPredicate pred = std::less<>()) {
    for (; first != last; ++first) {
        if (!std::is_sorted((*first).begin(), (*first).end(), pred)) {
            return false;
        }
    }

    return true;
}

template <typename ForwardIterator, typename BinaryPredicate>
void matrix_sort(ForwardIterator first, ForwardIterator last, BinaryPredicate pred = std::less<>()) {
    // Requires `create_linear_sequence` and `fill_from_linear_container`
    auto linear_matrix = create_linear_sequence(first, last);
    std::sort(linear_matrix.begin(), linear_matrix.end(), pred);

    fill_from_linear_container(first, last, linear_matrix);
}

template <typename ForwardIterator, typename Type = uint32_t>
[[nodiscard]] const Type matrix_trace(ForwardIterator first, ForwardIterator last, const Type& value = 0) {
    Type trace = value;
    const std::size_t n = std::distance(first, last);

    for (std::size_t i = 0; i < n; ++i, ++first) {
        trace += (*first)[i];
    }

    return trace;
}

CPL_END

#endif  // MATRIX_H_
