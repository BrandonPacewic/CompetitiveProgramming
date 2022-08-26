// output_matrix library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef OUTPUT_MATRIX_H_
#define OUTPUT_MATRIX_H_
#include <core.h>

#include <cstdint>
#include <functional>
#include <iostream>

CPL_BEGIN

template <typename T_matrix>
const void output_matrix(const T_matrix& matrix, const bool& space = true, const bool& new_line = true) {
    for (std::size_t row = 0; row < matrix.size(); ++row) {
        for (std::size_t col = 0; col < matrix[row].size(); ++col) {
            std::cout << matrix[row][col];

            if (space && col < matrix[row].size() - 1) {
                std::cout << ' ';
            }
        }

        std::cout << (new_line ? '\n' : ' ');
    }
}

template <typename T_matrix>
const void output_reverse_matrix(const T_matrix& matrix, const bool& space = true, const bool& new_line = true) {
    for (std::size_t row = matrix.size(); row > 0; --row) {
        for (std::size_t col = matrix[row - 1].size(); col > 0; --col) {
            std::cout << matrix[row - 1][col - 1];

            if (space && col > 1) {
                std::cout << ' ';
            }
        }

        std::cout << (new_line ? '\n' : ' ');
    }
}

const void output_empty_matrix(const uint16_t& rows, const uint16_t& cols, const char& primary, const char& secondary,
                               std::function<bool(uint16_t&, uint16_t&)> evaluation, const bool& space = false);

CPL_END

#endif  // OUTPUT_MATRIX_H_
