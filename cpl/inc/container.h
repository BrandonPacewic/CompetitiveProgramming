// container library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef CONTAINER_H_
#define CONTAINER_H_
#include "xcore.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <vector>

CPL_BEGIN

template <typename... Ts>
struct _Is_container_helper {};

template <typename T, typename = void>
struct _Is_container : std::false_type {};

template <typename T>
struct _Is_container<T, std::conditional_t<false,
                            _Is_container_helper<typename T::value_type, decltype(std::declval<T>().begin()),
                                decltype(std::declval<T>().end())>,
                            void>> : std::true_type {};

template <typename T>
constexpr bool is_container = _Is_container<T>::value;

#define CPL_IS_CONTAINER(T) static_assert(is_container<T>, "Templated parameter is not a valid container.")

template <class FwdIt1, class FwdIt2, class OutIt>
OutIt alternating_insertion(FwdIt1 first1, FwdIt1 last1, FwdIt2 first2, FwdIt2 last2, OutIt result) {
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

template <class InCont1, class InCont2, class OutCont>
[[nodiscard]] OutCont alternating_insertion(const InCont1& input1, const InCont2& input2, OutCont output) {
#if CPL
    CPL_IS_CONTAINER(InCont1);
    CPL_IS_CONTAINER(InCont2);
    CPL_IS_CONTAINER(OutCont);
#endif // CPL
    return alternating_insertion(
        input1.begin(), input1.end(), input2.begin(), input2.end(), std::back_inserter(output));
}

template <class FwdIt, class Ty = typename std::iterator_traits<FwdIt>::value_type>
[[nodiscard]] std::vector<std::pair<Ty, uint16_t>> run_length_encoding(FwdIt first, FwdIt last) {
    std::vector<std::pair<Ty, uint16_t>> encoding;
    if (first == last) {
        return encoding;
    }

    Ty       previous_item = *first;
    uint16_t current_count = 0;

    for (; first != last; ++first) {
        if (*first == previous_item) {
            ++current_count;
        } else {
            if (current_count) {
                encoding.emplace_back(previous_item, current_count);
            }

            previous_item = *first;
            current_count = 1;
        }
    }

    if (current_count) {
        encoding.emplace_back(previous_item, current_count);
    }

    return encoding;
}

template <class Cont, class Ty = typename Cont::value_type>
[[nodiscard]] std::vector<std::pair<Ty, uint16_t>> run_length_encoding(const Cont& container) {
#if CPL
    CPL_IS_CONTAINER(Cont);
#endif // CPL
    return run_length_encoding(container.begin(), container.end());
}

template <class FwdIt>
FwdIt merge_sort(FwdIt first, FwdIt last) {
    if (std::distance(first, last) > 1) {
        FwdIt middle = first + std::distance(first, last) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last);
    }

    return first;
}

template <class Cont>
Cont merge_sort(Cont& container) {
#if CPL
    CPL_IS_CONTAINER(Cont);
#endif // CPL

    merge_sort(container.begin(), container.end());
    return container;
}

template <class FwdIt>
FwdIt reverse_sort(FwdIt first, FwdIt last) {
    for (; first != last; ++first) {
        FwdIt min = std::min_element(first, last);
        std::reverse(first, min + 1);
    }

    return first;
}

template <class Cont>
Cont reverse_sort(Cont& container) {
#if CPL
    CPL_IS_CONTAINER(Cont);
#endif // CPL

    reverse_sort(container.begin(), container.end());
    return container;
}

CPL_END

#endif // CONTAINER_H_
