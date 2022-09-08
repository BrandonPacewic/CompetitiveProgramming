// extended cmath library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef ECMATH_H_
#define ECMATH_H_
#include <core.h>

#include <cstdint>

class int24 {
    int24(uint32_t value);

    void operator=(uint32_t value);
};


#endif // ECMATH_H_