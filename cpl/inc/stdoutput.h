// standard output library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef STD_OUTPUT_H_
#define STD_OUTPUT_H_
#include "xcore.h"

#include <iostream>

#include "container.h"

CPL_BEGIN

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

// Special overloads for runtime test output.
namespace debug {

    template <class Cont,
        class Valty = class std::enable_if<!std::is_same<Cont, std::string>::value, typename Cont::value_type>::type>
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

    template <class First, class Second>
    std::ostream& operator<<(std::ostream& os, const std::pair<First, Second>& pair) {
        return os << '(' << pair.first << ", " << pair.second << ')';
    }

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

} // namespace debug

CPL_END

#endif // STD_OUTPUT_H_
