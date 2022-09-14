// container library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <core.h>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <set>
#include <type_traits>
#include <unordered_set>
#include <vector>

CPL_BEGIN

// Container Validation
template <typename... Ts>
struct is_container_helper {};

template <typename T, typename = void>
struct is_container_internal : std::false_type {};

template <typename T>
struct is_container_internal<
    T, std::conditional_t<false,
                          is_container_helper<typename T::value_type, typename T::size_type, typename T::allocator_type,
                                              typename T::iterator, typename T::const_iterator,
                                              decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>,
                          void>> : std::true_type {};

template <typename T>
constexpr bool is_container = is_container_internal<T>::value;

// Combines two ranges of elements into one range, taking alternating elements from each range.
// (first1, last1] (first2, last2)
template <class ForwardIterator1, class ForwardIterator2, class OutputIterator>
OutputIterator alternating_insertion(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2,
                                     ForwardIterator2 last2, OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        *result++ = *first1++;
        *result++ = *first2++;
    }

    if (first1 != last1) {
        std::copy(first1, last1, result);
    } else if (first2 != last2) {
        std::copy(first2, last2, result);
    }

    return result;
}

template <typename ForwardIterator,
          typename BaseIteratorType = typename std::iterator_traits<ForwardIterator>::value_type>
[[nodiscard]] std::vector<std::pair<BaseIteratorType, uint16_t>> run_length_encoding(ForwardIterator first,
                                                                                     ForwardIterator last) {
    std::vector<std::pair<BaseIteratorType, uint16_t>> encoding;
    BaseIteratorType previous_item;
    uint16_t current_count = 0;

    for (; first != last; ++first) {
        if (*first == previous_item) {
            ++current_count;
        } else {  // Save current count and start again.
            if (current_count) {
                encoding.emplace_back(previous_item, current_count);
            }

            previous_item = *first;
            current_count = 1;
        }
    }

    if (current_count) {  // Leftover
        encoding.emplace_back(previous_item, current_count);
    }

    return encoding;
}

// Explicit ranges to set/unordered_set conversion.
template <typename ForwardIterator,
          typename BaseIteratorType = typename std::iterator_traits<ForwardIterator>::value_type>
[[nodiscard]] std::set<BaseIteratorType> to_set(ForwardIterator first, ForwardIterator last) {
    std::set<BaseIteratorType> set_obj(first, last);
    return set_obj;
}

template <typename ForwardIterator,
          typename BaseIteratorType = typename std::iterator_traits<ForwardIterator>::value_type>
[[nodiscard]] std::unordered_set<BaseIteratorType> to_unordered_set(ForwardIterator first, ForwardIterator last) {
    std::unordered_set<BaseIteratorType> set_obj(first, last);
    return set_obj;
}

template <typename T_container>
const void output_container(const T_container& container, const bool& space = true, const bool& new_line = true) {
    for (std::size_t i = 0; i < container.size(); ++i) {
        std::cout << container[i];

        if (space && i < container.size() - 1) {
            std::cout << ' ';
        }
    }

    std::cout << (new_line ? '\n' : ' ');
}

template <typename T_container>
const void output_reverse_container(const T_container& container, const bool& space = true,
                                    const bool& new_line = true) {
    for (std::size_t i = container.size(); i > 0; --i) {
        std::cout << container[i - 1];

        if (space && i > 1) {
            std::cout << ' ';
        }
    }

    std::cout << (new_line ? '\n' : ' ');
}

template <typename ForwardIterator>
void output_container(ForwardIterator first, ForwardIterator last, const bool& space = true,
                      const bool& new_line = true) {
    for (; first != last; ++first) {
        std::cout << *first;

        if (space && first != last - 1) {
            std::cout << ' ';
        }
    }

    std::cout << (new_line ? '\n' : ' ');
}

template <typename ForwardIterator>
void output_reverse_container(ForwardIterator first, ForwardIterator last, const bool& space = true,
                              const bool& new_line = true) {
    for (; first != last; ++first) {
        std::cout << *first;

        if (space && first != last - 1) {
            std::cout << ' ';
        }
    }

    std::cout << (new_line ? '\n' : ' ');
}

CPL_END

#endif  // CONTAINER_H_
