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
 *  Basic uniform matrix extending std::array.
 */

#include <array>
#include <cstddef>

template <class Ty, std::size_t N>
class basic_uniform_matrix {
   public:
    using value_type = Ty;
    using row_type = std::array<Ty, N>;
    using pointer = row_type*;
    using const_pointer = const row_type*;
    using reference = row_type&;
    using const_reference = const row_type&;
    using size_type = std::size_t;

    basic_uniform_matrix() = default;
    basic_uniform_matrix(const basic_uniform_matrix&) = default;
    basic_uniform_matrix(basic_uniform_matrix&&) = default;
    basic_uniform_matrix& operator=(const basic_uniform_matrix&) = default;
    basic_uniform_matrix& operator=(basic_uniform_matrix&&) = default;

    reference operator[](size_type index) { return rows[index]; }

    constexpr const_reference operator[](size_type index) const {
        return rows[index];
    }

    constexpr size_type size() const { return N; }

    constexpr pointer begin() { return rows.begin(); }

    constexpr const_pointer begin() const { return rows.begin(); }

    constexpr pointer end() { return rows.end(); }

    constexpr const_pointer end() const { return rows.end(); }

    reference front() { return rows.front(); }

    constexpr const_reference front() const { return rows.front(); }

    reference back() { return rows.back(); }

    constexpr const_reference back() const { return rows.back(); }

   private:
    std::array<std::array<Ty, N>, N> rows;
};