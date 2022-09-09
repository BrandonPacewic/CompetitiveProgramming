// ostream_overloads library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef OSTREAM_OVERLOADS_H_
#define OSTREAM_OVERLOADS_H_
#include <core.h>

#include <algorithm>
#include <ostream>
#include <string>

// Linear container output overload.
template <typename T_container, typename T = typename std::enable_if<!std::is_same<T_container, std::string>::value,
                                                                     typename T_container::value_type>::type>
std::ostream& operator<<(std::ostream& os, const T_container& container) {
    os << '{';
    std::string sep;

    for (const T& item : container) {
        os << sep << item, sep = ", ";
    }

    return os << '}';
}

// Pair output overload.
template <typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A, B>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

#endif  // OSTREAM_OVERLOADS_H_
