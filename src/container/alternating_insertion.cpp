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

/**
 *  @brief Combines two containers into one taking alternating elements.
 *  @param first1 Forward iterator to the first element of the first container.
 *  @param last1 Forward iterator to one past the last element of the first
 *               container.
 *  @param first2 Forward iterator to the first element of the second container.
 *  @param last2 Forward iterator to one past the last element of the second
 *               container.
 *  @param result Output iterator to the first element of the combined
 * container.
 *  @return Output iterator to the end of the combined container.
 */
template <class ForwardIterator1, class ForwardIterator2, class OutputIterator>
OutputIterator alternating_insertion(ForwardIterator1 first1,
                                     ForwardIterator1 last1,
                                     ForwardIterator2 first2,
                                     ForwardIterator2 last2,
                                     OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        *result++ = *first1++;
        *result++ = *first2++;
    }

    if (first1 != last1) {
        std::copy(first1, last1, result);
    } else if (first2 != last2) {
        std::copy(first2, last2, result);
    }

    return result;
}