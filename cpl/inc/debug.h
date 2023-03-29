// debug library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef DEBUG_H_
#define DEBUG_H_
#include <core.h>
#include <ostream_overloads.h>

#include <iostream>

#if DBG_MODE || CPL
void dbg_out() {
    std::cerr << std::endl;
}

template <typename Head, typename... Tail>
void dbg_out(Head A, Tail... B) {
    std::cerr << ' ' << A;
    dbg_out(B...);
}

#define test(...) std::cerr << "[" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else  // ^^^ DBG_MODE || CPL ^^^ / vvv !DBG_MODE && !CPL
#define test(...)
#endif  // DBG_MODE || CPL

#endif  // DEBUG_H_
