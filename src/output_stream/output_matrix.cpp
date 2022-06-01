/* MIT License
 *
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>

template <typename T_matrix>
const void output_matrix(const T_matrix& matrix, const bool& space = true,
                         const bool& new_line = true) {
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
const void output_reverse_matrix(const T_matrix& matrix,
                                 const bool& space = true,
                                 const bool& new_line = true) {
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