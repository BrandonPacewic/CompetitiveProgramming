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

/**
 * @file matrix/basic_uniform_matrix.h
 * @author Brandon Pacewic
 * This file contains the shell of the uniform_matrix class.
 * Move needed functions into this file as needed.
 */

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row {
   public:
    typedef Ty* pointer;
    typedef const Ty* const_pointer;
    typedef Ty& reference;
    typedef const Ty& const_reference;
    typedef std::size_t size_type;
    typedef Ty value_type;

    _uniform_matrix_row() {}

    _uniform_matrix_row(size_type& _n)
        : elements{std::make_unique<value_type[]>(_n)}, length{_n} {}

    _uniform_matrix_row(size_type& _n, const value_type& _value)
        : elements{std::make_unique<value_type[]>(_n)}, length{_n} {
        std::fill(elements.get(), elements.get() + length, _value);
    }

    const size_type& size() const { return length; }

    pointer begin() noexcept { return &elements[0]; }
    const const_pointer begin() const noexcept { return &elements[0]; }

    pointer end() noexcept { return &elements[length]; }
    const const_pointer end() const noexcept { return &elements[length]; }

    reference front() noexcept { return elements[0]; }
    const_reference front() const noexcept { return elements[0]; }

    reference back() noexcept { return elements[length - 1]; }
    const_reference back() const noexcept { return elements[length - 1]; }

    reference operator[](const size_type& i) { return elements[i]; }
    const_reference operator[](const size_type& i) const { return elements[i]; }

   private:
    std::unique_ptr<value_type[]> elements;
    size_type length;
};

template <class Ty>
class uniform_matrix {
   public:
    typedef _uniform_matrix_row<Ty> row_type;
    typedef row_type* row_pointer;
    typedef const row_type* const_row_pointer;
    typedef Ty* type_pointer;
    typedef const Ty* type_const_pointer;
    typedef row_type& row_reference;
    typedef const row_type& const_row_roference;
    typedef Ty& type_reference;
    typedef const Ty& type_const_reference;
    typedef std::size_t size_type;
    typedef Ty value_type;

    uniform_matrix(size_type _n)
        : rows{std::make_unique<row_type[]>(_n)}, row_length{_n} {
        for (size_type i = 0; i < row_length; ++i) {
            rows[i] = row_type(row_length);
        }
    }

    uniform_matrix(size_type _n, const value_type& _value)
        : rows{std::make_unique<row_type[]>(_n)}, row_length{_n} {
        for (size_type i = 0; i < row_length; ++i) {
            rows[i] = row_type(row_length, _value);
        }
    }

    const size_type& size() const { return row_length; }

    template <typename ReturnValue = size_type>
    const ReturnValue total_size() const {
        return (ReturnValue)row_length * row_length;
    }

    row_pointer begin() { return &rows[0]; }
    const const_row_pointer begin() const { return &rows[0]; }

    row_pointer end() { return &rows[row_length]; }
    const const_row_pointer end() const { return &rows[row_length]; }

    row_reference front() { return *begin(); }
    const_row_roference front() const { return *begin(); }

    row_reference back() { return *(end() - 1); }
    const_row_roference back() const { return *(end() - 1); }

    row_reference operator[](const size_type& i) { return rows[i]; }
    const_row_roference operator[](const size_type& i) const { return rows[i]; }

    void for_each(std::function<void(value_type&)> function) {
        for (size_type row = 0; row < row_length; ++row) {
            for (size_type cell = 0; cell < row_length; ++cell) {
                function(rows[row][cell]);
            }
        }
    }

    void for_each(
        std::function<void(value_type&, size_type&, size_type&)> function) {
        for (size_type row = 0; row < row_length; ++row) {
            for (size_type cell = 0; cell < row_length; ++cell) {
                function(rows[row][cell], row, cell);
            }
        }
    }

   private:
    std::unique_ptr<row_type[]> rows;
    size_type row_length;
};