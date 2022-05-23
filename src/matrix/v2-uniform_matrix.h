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

/** @file matrix/uniform_matrix.h
 *  @author Brandon Pacewic
 *  This file contains the complete code for uniform_matrix.
 *  Code snippets can be moved into the basic_uniform_matrix class as needed.
 */

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <vector>

template <class Ty>
class uniform_matrix_row_segment {
public:
    using value_type = Ty;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;

    uniform_matrix_row_segment(pointer begin_pointer_, size_type n_) 
        : begin_pointer(begin_pointer_), n(n_) {}

    reference operator[](const size_type& index) const noexcept {
        return begin_pointer[index];
    }

    size_type size() const noexcept { return n; }

    pointer begin() noexcept { return begin_pointer; }
    const_pointer begin() const noexcept { return begin_pointer; }

    pointer end() noexcept { return begin_pointer + n; }
    const_pointer end() const noexcept { return begin_pointer + n; }

    const_pointer cbegin() const noexcept { return begin_pointer; }

    const_pointer cend() const noexcept { return begin_pointer + n; }

    const_pointer cdata() const noexcept { return begin_pointer; }

    reference front() noexcept { return *begin(); }
    const_reference front() const noexcept { return *begin(); }

    reference back() noexcept { return *(end() - 1); }
    const_reference back() const noexcept { return *(end() - 1); }



private:
    pointer begin_pointer;
    size_type n;
};

template <class Ty, std::size_t N>
class uniform_matrix {
public:
    using value_type = Ty;
    using value_pointer = Ty*;
    using value_reference = Ty&;
    using const_value_pointer = const Ty*;
    using const_value_reference = const Ty&;
    using size_type = std::size_t;

private:
    std::vector<value_type> data;
};