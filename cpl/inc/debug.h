// debug library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef DEBUG_H_
#define DEBUG_H_
#include <core.h>

#include <iostream>

#if defined(DBG_MODE) || defined(IS_CPL_LIBRARY_COMPILATION)
void dbg_out() {
    std::cerr << std::endl;
}

template <typename Head, typename... Tail>
void dbg_out(Head A, Tail... B) {
    std::cerr << ' ' << A;
    dbg_out(B...);
}

#define test(...) std::cerr << "[" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else  // ^^^ defined(DBG_MODE) || defined(IS_CPL_LIBRARY_COMPILATION) ^^^ / vvv !defined(DBG_MODE) &&
       // !defined(IS_CPL_LIBRARY_COMPILATION) vvv
#define test(...)
#endif  // !defined(DBG_MODE) && !defined(IS_CPL_LIBRARY_COMPILATION)

#endif  // DEBUG_H_
