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

#include <assert.h>

#include <vector>

#include "../../../src/matrix/matrix_algorithms.cpp"

int main() {
    using namespace std;

    vector<vector<int>> matrix(3, vector<int>(3, 0));

    assert(!matrix_any_of(matrix.begin(), matrix.end(),
                          [](const auto& item) { return item == 1; }));

    matrix[1][1] = 2;

    assert(matrix_any_of(matrix.begin(), matrix.end(),
                         [](const auto& item) { return item == 2; }));

    assert(!matrix_all_of(matrix.begin(), matrix.end(),
                          [](const auto& item) { return item == 1; }));
}