// sort library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef SORT_H_
#define SORT_H_
#include <core.h>

#include <algorithm>
#include <cstdint>

CPL_BEGIN

template <typename T_container>
[[nodiscard]] T_container internal_merge(T_container& container, std::size_t leftIndex, std::size_t middleIndex,
                                         std::size_t rightIndex) {
    T_container left_array(container.begin() + leftIndex, container.begin() + middleIndex + 1);
    T_container right_array(container.begin() + middleIndex + 1, container.begin() + rightIndex + 1);

    std::size_t left_index = 0, right_index = 0, merged_index = leftIndex;

    while (left_index < left_array.size() && right_index < right_array.size()) {
        if (left_array[left_index] <= right_array[right_index]) {
            container[merged_index] = left_array[left_index];
            ++left_index;
        } else {
            container[merged_index] = right_array[right_index];
            ++right_index;
        }
        ++merged_index;
    }

    while (left_index < left_array.size()) {
        container[merged_index] = left_array[left_index];
        ++left_index;
        ++merged_index;
    }

    while (right_index < right_array.size()) {
        container[merged_index] = right_array[right_index];
        ++right_index;
        ++merged_index;
    }

    return container;
}

template <typename T_container>
[[nodiscard]] T_container merge_sort(T_container& container, std::size_t left_index, std::size_t right_index) {
    if (left_index < right_index) {
        std::size_t middle_index = left_index + (right_index - left_index) / 2;

        merge_sort(container, left_index, middle_index);
        merge_sort(container, middle_index + 1, right_index);
        internal_merge(container, left_index, middle_index, right_index);
    }

    return container;
}

template <typename T_container>
[[nodiscard]] T_container reverse_sort(T_container& container) {
    std::for_each(container.begin(), container.end(), [&](auto& element, const auto& i) {
        auto index = std::min_element(container.begin() + i, container.end());
        std::reverse(container.begin() + i, container.begin() + index + 1);
    });

    return container;
}

CPL_END

#endif  // SORT_H_
