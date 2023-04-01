// core internal header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef CORE_H_
#define CORE_H_

#define CPL_STRINGIZE_(S) #S
#define CPL_STRINGIZE(S) CPL_STRINGIZE_(S)

// CPL compiler checks
#ifndef __cplusplus
#pragma message(__FILE__ "(" CPL_STRINGIZE(__LINE__) "): CPL: Unexpected compiler, expected C++ compiler.")
#error Error in C++ CPL usage; Unsupported compiler.
#endif // __cplusplus

// TRANSITION GH-101
// Currently not able to detect MSVC /std:c++20

// CPL requires C++20 or later.
// #if !(__cplusplus >= 202002L)
// #pragma message(__FILE__ "(" CPL_STRINGIZE(__LINE__) "): CPL: Unexpected compiler, expected C++20 compiler")
// #error Error in C++ CPL usage; Unsupported compiler.
// #endif  // !(__cplusplus >= 202002L)

// TRANSITION GH-101

#define CPL_BEGIN namespace cpl {
#define CPL_END }

// Used to allow for code segments to compile outside of the library.
// All macro library checks must first satisfy the `CPL` check.
#define CPL 1

#undef CPL_STRINGIZE_
#undef CPL_STRINGIZE

#endif // CORE_H_
