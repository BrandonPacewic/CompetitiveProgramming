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

#include <cstdint>
#include <vector>

template <typename ForwardIterator,
          typename BaseIteratorType =
              typename std::iterator_traits<ForwardIterator>::value_type>
[[nodiscard]] std::vector<std::pair<BaseIteratorType, uint16_t>>
run_length_encoding(ForwardIterator first, ForwardIterator last) {
    std::vector<std::pair<BaseIteratorType, uint16_t>> encoding;
    BaseIteratorType previous_item;
    uint16_t current_count = 0;

    for (; first != last; ++first) {
        if (*first == previous_item) {
            ++current_count;
        } else {
            if (current_count) {
                encoding.emplace_back(previous_item, current_count);
            }

            previous_item = *first;
            current_count = 1;
        }
    }

    if (current_count) {
        encoding.emplace_back(previous_item, current_count);
    }

    return encoding;
}