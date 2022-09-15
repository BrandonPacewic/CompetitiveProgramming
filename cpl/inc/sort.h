// sort library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef SORT_H_
#define SORT_H_
#include <container.h>
#include <core.h>

#include <algorithm>
#include <cstdint>

CPL_BEGIN

template <typename ForwardIterator>
ForwardIterator merge_sort(ForwardIterator first, ForwardIterator last) {
    if (std::distance(first, last) > 1) {
        ForwardIterator middle = first + std::distance(first, last) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last);
    }

    return first;
}

template <typename T_container>
T_container merge_sort(T_container& container) {
#if defined(IS_CPL_LIBRARY_COMPILATION)
    CPL_IS_CONTAINER(T_container);
#endif  // IS_CPL_LIBRARY_COMPILATION

    merge_sort(container.begin(), container.end());
    return container;
}

template <typename ForwardIterator>
ForwardIterator reverse_sort(ForwardIterator first, ForwardIterator last) {
    for (; first != last; ++first) {
        ForwardIterator min = std::min_element(first, last);
        std::reverse(first, min + 1);
    }

    return first;
}

template <typename T_container>
T_container reverse_sort(T_container& container) {
#if defined(IS_CPL_LIBRARY_COMPILATION)
    CPL_IS_CONTAINER(T_container);
#endif  // IS_CPL_LIBRARY_COMPILATION

    reverse_sort(container.begin(), container.end());
    return container;
}

CPL_END

#endif  // SORT_H_
