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

/** @file matrix/basic_uniform_matrix.h
 *  @author Brandon Pacewic
 *  This file contains the shell of the uniform_matrix class.
 *  Move needed functions into this file as needed.
 */

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class uniform_matrix_row {
   public:
    typedef Ty* pointer;
    typedef const Ty* const_pointer;
    typedef Ty& reference;
    typedef const Ty& const_reference;
    typedef std::size_t size_type;
    typedef Ty value_type;

    /**
     *  @brief Constructs an empty uniform_matrix_row.
     *
     *  Never construct this object outside of an @a uniform_matrix object
     */
    uniform_matrix_row() {}

    /**
     *  @brief Constructs an uniform_matrix_row with a given size.
     *  @param t_n Number of elements in the row.
     *
     *  Never construct this object outside of an @a uniform_matrix object
     */
    uniform_matrix_row(size_type& t_n)
        : elements{std::make_unique<value_type[]>(t_n)}, length{t_n} {}

    /**
     *  @brief Constructs an uniform_matrix_row with a given size and value.
     *  @param t_n Number of elements in the row.
     *  @param t_value Value to initialize each element with.
     *
     *  Never construct this object outside of an @a uniform_matrix object
     */
    uniform_matrix_row(size_type& t_n, const value_type& t_value)
        : elements{std::make_unique<value_type[]>(t_n)}, length{t_n} {
        std::fill(elements.get(), elements.get() + length, t_value);
    }

    /**
     *  @brief Returns the number of elements in the row.
     *  @return Number of elements in the row.
     */
    const size_type size() const { return length; }

    /**
     *  @brief Returns a pointer to the first element in the row.
     *  @return Pointer to the first element in the row.
     */
    pointer begin() noexcept { return &elements[0]; }

    /**
     *  @brief Returns a constant pointer to the first element in the row.
     *  @return Constant pointer to the first element in the row.
     */
    const const_pointer begin() const noexcept { return &elements[0]; }

    /**
     *  @brief Returns a pointer to the element one past the last element in
     *         the row.
     *  @return Pointer to the element one past the last element in the row.
     */
    pointer end() noexcept { return &elements[length]; }

    /**
     *  @brief Returns a constant pointer to the element one past the last
     *         element in the row.
     *  @return Constant pointer to the element one past the last element in
     *          the row.
     */
    const const_pointer end() const noexcept { return &elements[length]; }

    /**
     * @brief Returns a reference to the first element in the row.
     * @return reference to the first element in the row.
     */
    reference front() noexcept { return *begin(); }

    /**
     * @brief Returns a constant reference to the first element in the row.
     * @return constant reference to the first element in the row.
     */
    const_reference front() const noexcept { return *begin(); }

    /**
     * @brief Returns a reference to the last element in the row.
     * @return reference to the last element in the row.
     */
    reference back() noexcept { return *(end() - 1); }

    /**
     * @brief Returns a constant reference to the last element in the row.
     * @return constant reference to the last element in the row.
     */
    const_reference back() const noexcept { return *(end() - 1); }

    /**
     * @brief Returns a reference to the element at the given index.
     * @param index Index of the element to return.
     * @return reference to the element at the given index.
     */
    reference operator[](const size_type& index) { return elements[index]; }

    /**
     * @brief Returns a constant reference to the element at the given index.
     * @param index Index of the element to return.
     * @return constant reference to the element at the given index.
     */
    const_reference operator[](const size_type& index) const {
        return elements[index];
    }

   private:
    std::unique_ptr<value_type[]> elements;
    size_type length;
};

template <class Ty>
class uniform_matrix {
   public:
    typedef uniform_matrix_row<Ty> row_type;
    typedef row_type* row_pointer;
    typedef const row_type* const_row_pointer;
    typedef Ty* type_pointer;
    typedef const Ty* const_type_pointer;
    typedef row_type& row_reference;
    typedef const row_type& const_row_reference;
    typedef Ty& type_reference;
    typedef const Ty& const_type_reference;
    typedef std::size_t size_type;
    typedef Ty value_type;

    /**
     *  @brief Constructs an uniform_matrix object with a given size
     *  @param t_n Number of rows and columns in the matrix.
     */
    uniform_matrix(size_type t_n)
        : rows{std::make_unique<row_type[]>(t_n)}, row_length{t_n} {
        for (size_type i = 0; i < row_length; ++i) {
            rows[i] = row_type(row_length);
        }
    }

    /**
     *  @brief Constructs an uniform_matrix object with a given size and value
     *  @param t_n Number of rows and columns in the matrix.
     *  @param t_value Value to initialize each element with.
     */
    uniform_matrix(size_type t_n, const value_type& t_value)
        : rows{std::make_unique<row_type[]>(t_n)}, row_length{t_n} {
        for (size_type i = 0; i < row_length; ++i) {
            rows[i] = row_type(row_length, t_value);
        }
    }

    /**
     *  @brief Applies the given function to each element in the matrix.
     *  @param function The function to apply.
     *
     *  There are two definitions of this function. One with a std::function
     *  of return type void and of one argument value_type reference, and
     *  one with a std::function of return type void and of three arguments
     *  value_type reference, size_type reference of the current row, and
     *  size_type reference of the current column.
     */
    void for_each(std::function<void(value_type&)> function) {
        for (row_reference& row : *this) {
            for (type_reference& cell : row) {
                function(cell);
            }
        }
    }

    /**
     *  @brief Applies the given function to each element in the matrix.
     *  @param function The function to apply.
     *
     *  Second definition of the uniform_matrix::for_each function. Note that
     *  any other function that needs to be range restricted should use this
     *  template function as a starting point as it is the only way to loop
     *  through the matrix while retrieving the current cell index of the
     *  element.
     */
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