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

#include <algorithm>
#include <cstdint>
#include <vector>

template <typename T, typename T_iterable>
std::vector<std::pair<T, uint16_t>> run_length_encoding(
    const T_iterable& items) {
    std::vector<std::pair<T, uint16_t>> encoding;
    T previous_item;
    uint16_t current_count = 0;

    std::for_each(items.begin(), items.end(), [&](const T& item) {
        if (item == previous_item) {
            ++current_count;
        } else {
            if (current_count) {
                encoding.emplace_back(previous_item, current_count);
            }

            previous_item = item;
            current_count = 1;
        }
    });

    if (current_count) {
        encoding.emplace_back(previous_item, current_count);
    }

    return encoding;
}