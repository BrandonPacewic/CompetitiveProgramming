// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

// implement output_empty_matrix

#include <matrix.h>

#include <functional>
#include <iostream>

const void output_empty_matrix(const uint16_t& rows, const uint16_t& cols, const char& primary, const char& secondary,
                               std::function<bool(uint16_t&, uint16_t&)> evaluation, const bool& space = false) {
    for (uint16_t row = 0; row < rows; ++row) {
        for (uint16_t col = 0; col < cols; ++col) {
            std::cout << (evaluation(row, col) ? primary : secondary);

            if (space && col < cols - 1) {
                std::cout << ' ';
            }
        }

        std::cout << '\n';
    }
}
