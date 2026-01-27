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
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

CPL_BEGIN

// ostream overloads for debugging output
template <class First, class Second>
std::ostream& operator<<(std::ostream& os, const std::pair<First, Second>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

template <typename Cont,
    class Valty = typename std::enable_if<!std::is_same<Cont, std::string>::value, typename Cont::value_type>::type>
std::ostream& operator<<(std::ostream& os, const Cont& container) {
    os << '{';
    auto it  = container.begin();
    auto end = container.end();

    if (it != end) {
        os << *it;
        ++it;
    }

    for (; it != end; ++it) {
        os << ", " << *it;
    }

    return os << '}';
}

// macros for debugging output
#if DBG_MODE || CPL
template <class... Args>
void dbg_out() {
    std::cerr << std::endl;
}

template <class Head, class... Tail>
void dbg_out(Head&& head, Tail&&... tail) {
    std::cerr << ' ' << head;
    dbg_out(std::forward<Tail>(tail)...);
}

#define test(...) std::cerr << "[" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else // ^^^ DBG_MODE || CPL ^^^ / vvv !DBG_MODE && !CPL
#define test(...)
#endif // DBG_MODE || CPL

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

template <class FwdIter>
const void output_container(FwdIter first, FwdIter last, const bool& space = true, const bool& new_line = true) {
    for (; first != last; ++first) {
        std::cout << *first;

        if (space && first != last - 1) {
            std::cout << ' ';
        }
    }

    std::cout << (new_line ? '\n' : ' ');
}

template <typename Cont>
const void output_container(const Cont& container, const bool& space = true, const bool& new_line = true) {
#if CPL
    CPL_IS_CONTAINER(Cont);
#endif // CPL
    output_container(container.begin(), container.end(), space, new_line);
}

template <class FwdIter>
const void output_reverse_container(
    FwdIter first, FwdIter last, const bool& space = true, const bool& new_line = true) {
    for (; first != last; ++first) {
        std::cout << *first;

        if (space && first != last - 1) {
            std::cout << ' ';
        }
    }

    std::cout << (new_line ? '\n' : ' ');
}

template <typename Cont>
const void output_reverse_container(const Cont& container, const bool& space = true, const bool& new_line = true) {
#if CPL
    CPL_IS_CONTAINER(Cont);
#endif // CPL
    output_reverse_container(container.rbegin(), container.rend(), space, new_line);
}

template <class... Args>
auto alternating_insertion(Args&&... args) {
    // 3-arg -> Treat arguments as containers, e.g. (input1, input2, output)
    // 5-arg -> Treat arguments as iterators, e.g. (first1, last1, first2, last2, result)
    auto [first1, last1, first2, last2, result] = [](Args&&... args) {
        if constexpr (sizeof...(args) == 3) {
            auto&& [in1, in2, out] = std::forward_as_tuple(args...);
            return std::tuple(in1.begin(), in1.end(), in2.begin(), in2.end(), out.begin());
        } else if constexpr (sizeof...(args) == 5) {
            return std::tuple(std::forward<Args>(args)...);
        } else {
            static_assert(false, "Invalid number of arguments");
        }
    }(std::forward<Args>(args)...);

    while (first1 != last1 && first2 != last2) {
        *result = *first1;
        ++result;
        ++first1;

        *result = *first2;
        ++result;
        ++first2;
    }

    if (first1 != last1) {
        std::copy(first1, last1, result);
    } else if (first2 != last2) {
        std::copy(first2, last2, result);
    }

    return result;
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
