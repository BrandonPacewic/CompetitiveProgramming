// container library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <core.h>

#include <algorithm>
#include <cstdint>
#include <set>
#include <unordered_set>
#include <vector>

CPL_BEGIN

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
        } else { // Save current count and start again.
            if (current_count) {
                encoding.emplace_back(previous_item, current_count);
            }

            previous_item = *first;
            current_count = 1;
        }
    }

    if (current_count) { // Leftover
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

CPL_END

#endif  // CONTAINER_H_