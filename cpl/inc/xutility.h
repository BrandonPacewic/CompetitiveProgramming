// xutility library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef XUTILITY_H_
#define XUTILITY_H_
#include "xcore.h"

#include <functional>
#include <type_traits>

CPL_BEGIN

// The following effectively implements recursive lambdas.
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template <class Fun>
class y_combinator_result {
    Fun fun;

public:
    template <class T>
    explicit y_combinator_result(T&& fun) : fun(std::forward<T>(fun)) {}

    template <class... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

CPL_END

#endif // XUTILITY_H_
