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

#include <algorithm>
#include <cstdint>

template <typename T_container>
T_container merge(T_container& container, std::size_t leftIndex,
                  std::size_t middleIndex, std::size_t rightIndex) {
    T_container left_array(container.begin() + leftIndex,
                           container.begin() + middleIndex + 1);
    T_container right_array(container.begin() + middleIndex + 1,
                            container.begin() + rightIndex + 1);

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
T_container merge_sort(T_container& container, std::size_t left_index,
                       std::size_t right_index) {
    if (left_index < right_index) {
        std::size_t middle_index = left_index + (right_index - left_index) / 2;

        merge_sort(container, left_index, middle_index);
        merge_sort(container, middle_index + 1, right_index);
        merge(container, left_index, middle_index, right_index);
    }

    return container;
}