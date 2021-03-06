/* MIT License
 *
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// Adapted STL Algorithms for working with a 2-dimensional container

#include <algorithm>
#include <functional>
#include <vector>

template <class ForwardIterator, class UnaryPredicate>
[[nodiscard]] const bool matrix_any_of(ForwardIterator first,
                                       ForwardIterator last,
                                       UnaryPredicate pred) {
    for (; first != last; ++first) {
        if (std::any_of((*first).begin(), (*first).end(), pred)) {
            return true;
        }
    }

    return false;
}

template <class ForwardIterator, class UnaryPredicate>
[[nodiscard]] const bool matrix_all_of(ForwardIterator first,
                                       ForwardIterator last,
                                       UnaryPredicate pred) {
    for (; first != last; ++first) {
        if (!std::all_of((*first).begin(), (*first).end(), pred)) {
            return false;
        }
    }

    return true;
}

template <class ForwardIterator, class UnaryPredicate>
[[nodiscard]] const bool matrix_none_of(ForwardIterator first,
                                        ForwardIterator last,
                                        UnaryPredicate pred) {
    for (; first != last; ++first) {
        if (!std::none_of((*first).begin(), (*first).end(), pred)) {
            return false;
        }
    }

    return true;
}

template <class ForwardIterator, class ValueType>
void matrix_fill(ForwardIterator first, ForwardIterator last,
                 const ValueType& value) {
    for (; first != last; ++first) {
        std::fill((*first).begin(), (*first).end(), value);
    }
}

template <class ForwardIterator, class ValueType>
[[nodiscard]] const ForwardIterator matrix_find(ForwardIterator first,
                                                ForwardIterator last,
                                                const ValueType& value) {
    for (; first != last; ++first) {
        const auto it = std::find((*first).begin(), (*first).end(), value);

        if (it != (*first).end()) {
            return it;
        }
    }

    return last.end();
}

template <class ForwardIterator, class UnaryPredicate>
[[nodiscard]] const ForwardIterator matrix_find_if(ForwardIterator first,
                                                   ForwardIterator last,
                                                   UnaryPredicate pred) {
    for (; first != last; ++first) {
        const auto it = std::find_if((*first).begin(), (*first).end(), pred);

        if (it != (*first).end()) {
            return it;
        }
    }

    return last;
}

template <class ForwardIterator, class UnaryFunction>
UnaryFunction matrix_for_each(ForwardIterator first, ForwardIterator last,
                              UnaryFunction func) {
    for (; first != last; ++first) {
        std::for_each((*first).begin(), (*first).end(), func);
    }

    return func;
}

template <class ForwardIterator, class LinearContainer>
void fill_from_linear_container(ForwardIterator first, ForwardIterator last,
                                const LinearContainer& container) {
    std::size_t linear_index = 0;

    for_each(first, last, [&](auto& cell) {
        cell = container[linear_index], ++linear_index;
    });

#ifdef DBG_MODE  // Extra cost of time complexity
    auto linear_container_size =
        std::distance(container.begin(), container.end());

    if (linear_index != linear_container_size) {
        throw std::out_of_range(
            "fill_from_linear: container size does not "
            "match matrix size; invalid conversion of "
            "linear container to matrix");
    }
#endif
}

template <class ForwardIterator, class ValueType>
void matrix_iota(ForwardIterator first, ForwardIterator last, ValueType value) {
    for (; first != last; ++first) {
        for (auto itr = (*first).begin(); itr != (*first).end(); ++itr) {
            *itr = value;
            ++value;
        }
    }
}

template <class ForwardIterator, class ValueType,
          class ReturnContainerType = std::vector<ValueType>>
[[nodiscard]] ReturnContainerType create_linear_sequence(ForwardIterator first,
                                                         ForwardIterator last) {
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

template <class ForwardIterator, class BinaryPredicate>
[[nodiscard]] const bool matrix_is_sorted(
    ForwardIterator first, ForwardIterator last,
    BinaryPredicate pred = std::less<>()) {
    for (; first != last; ++first) {
        if (!std::is_sorted((*first).begin(), (*first).end(), pred)) {
            return false;
        }
    }

    return true;
}

template <class ForwardIterator, class BinaryPredicate>
void matrix_sort(ForwardIterator first, ForwardIterator last,
                 BinaryPredicate pred = std::less<>()) {
    /// Requires `create_linear_sequence` and `fill_from_linear_container`
    auto linear_matrix = create_linear_sequence(first, last);
    std::sort(linear_matrix.begin(), linear_matrix.end(), pred);

    fill_from_linear_container(first, last, linear_matrix);
}
