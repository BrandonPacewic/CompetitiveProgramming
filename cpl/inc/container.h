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
                          is_container_helper<typename T::value_type, decltype(std::declval<T>().begin()),
                                              decltype(std::declval<T>().end())>,
                          void>> : std::true_type {};

template <typename T>
constexpr bool is_container = is_container_internal<T>::value;

#define CPL_IS_CONTAINER(T) static_assert(is_container<T>, "Templated parameter is not a valid container.")

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

template <class InputContainer1, class InputContainer2, class OutputContainer>
OutputContainer alternating_insertion(const InputContainer1& input1, const InputContainer2& input2,
                                      OutputContainer output) {
#if defined(CPL_IS_CONTAINER)
    CPL_IS_CONTAINER(InputContainer1);
    CPL_IS_CONTAINER(InputContainer2);
    CPL_IS_CONTAINER(OutputContainer);
#endif

    return alternating_insertion(input1.begin(), input1.end(), input2.begin(), input2.end(), output.begin());
}

template <typename ForwardIterator,
          typename BaseIteratorType = typename std::iterator_traits<ForwardIterator>::value_type>
[[nodiscard]] std::vector<std::pair<BaseIteratorType, uint16_t>> run_length_encoding(ForwardIterator first,
                                                                                     ForwardIterator last) {
    std::vector<std::pair<BaseIteratorType, uint16_t>> encoding;

    if (first == last) {
        return encoding;
    }

    BaseIteratorType previous_item = *first;
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

template <typename T_container, typename ContainerValueType = typename T_container::value_type>
[[nodiscard]] std::vector<std::pair<ContainerValueType, uint16_t>> run_length_encoding(const T_container& container) {
#if defined(CPL_IS_CONTAINER)
    CPL_IS_CONTAINER(T_container);
#endif

    return run_length_encoding(container.begin(), container.end());
}

// set / unordered_set conversions.
template <typename ForwardIterator,
          typename BaseIteratorType = typename std::iterator_traits<ForwardIterator>::value_type>
[[nodiscard]] std::set<BaseIteratorType> to_set(ForwardIterator first, ForwardIterator last) {
    std::set<BaseIteratorType> set_obj(first, last);
    return set_obj;
}

template <typename T_container, typename ContainerValueType = typename T_container::value_type>
[[nodiscard]] std::set<ContainerValueType> to_set(const T_container& container) {
#if defined(CPL_IS_CONTAINER)
    CPL_IS_CONTAINER(T_container);
#endif

    return to_set(container.begin(), container.end());
}

template <typename ForwardIterator,
          typename BaseIteratorType = typename std::iterator_traits<ForwardIterator>::value_type>
[[nodiscard]] std::unordered_set<BaseIteratorType> to_unordered_set(ForwardIterator first, ForwardIterator last) {
    std::unordered_set<BaseIteratorType> set_obj(first, last);
    return set_obj;
}

template <typename T_container, typename ContainerValueType = typename T_container::value_type>
[[nodiscard]] std::unordered_set<ContainerValueType> to_unordered_set(const T_container& container) {
#if defined(CPL_IS_CONTAINER)
    CPL_IS_CONTAINER(T_container);
#endif

    return to_unordered_set(container.begin(), container.end());
}

// container output templates
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

template <typename T_container>
const void output_container(const T_container& container, const bool& space = true, const bool& new_line = true) {
#if defined(CPL_IS_CONTAINER)
    CPL_IS_CONTAINER(T_container);
#endif  // IS_CPL_LIBRARY_COMPILATION

    output_container(container.begin(), container.end(), space, new_line);
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

template <typename T_container>
const void output_reverse_container(const T_container& container, const bool& space = true,
                                    const bool& new_line = true) {
#if defined(CPL_IS_CONTAINER)
    CPL_IS_CONTAINER(T_container);
#endif  // IS_CPL_LIBRARY_COMPILATION

    output_reverse_container(container.rbegin(), container.rend(), space, new_line);
}

CPL_END

#endif  // CONTAINER_H_
