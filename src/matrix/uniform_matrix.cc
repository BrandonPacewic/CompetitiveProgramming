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
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_set>

template <typename Ty>
class _uniform_matrix_row {
   public:
    using iterator = Ty*;
    using const_iterator = const Ty*;
    using reference = Ty&;
    using const_reference = const Ty&;
    using size_type = std::size_t;
    using size_type_reference = size_type&;

    _uniform_matrix_row() {}

    _uniform_matrix_row(size_type_reference _n)
        : elements{std::make_unique<Ty[]>(_n)}, n{_n} {}

    _uniform_matrix_row(size_type_reference _n, const Ty& _element)
        : elements{std::make_unique<Ty[]>(_n)}, n{_n} {
        std::fill(elements.get(), elements.get() + n, _element);
    }

    size_type_reference size() { return n; }

    iterator begin() { return &elements[0]; }
    const const_iterator begin() const { return &elements[0]; }

    iterator end() { return &elements[n]; }
    const const_iterator end() const { return &elements[n]; }

    reference operator[](const int& i) { return elements[i]; }
    const_reference operator[](const int& i) const { return elements[i]; }

   private:
    std::unique_ptr<Ty[]> elements;
    size_type n;
};

template <typename Ty>
class uniform_matrix {
   public:
    using row_type = _uniform_matrix_row<Ty>;
    using iterator = row_type*;
    using const_iterator = const row_type*;
    using reference = row_type&;
    using const_reference = const row_type&;
    using size_type = std::size_t;
    using size_type_reference = size_type&;

    uniform_matrix(size_type _n)
        : rows{std::make_unique<row_type[]>(_n)}, n{_n}, total_n{_n * _n} {
        for (size_type i = 0; i < n; ++i) {
            rows[i] = _uniform_matrix_row<Ty>(n);
        }
    }

    uniform_matrix(size_type _n, const Ty& _element)
        : rows{std::make_unique<row_type[]>(_n)}, n{_n} {
        for (size_type i = 0; i < n; ++i) {
            rows[i] = row_type(n, _element);
        }
    }

    size_type_reference size() { return n; }
    size_type_reference total_size() { return total_n; }

    iterator begin() { return &rows[0]; }
    const const_iterator begin() const { return &rows[0]; }

    iterator end() { return &rows[n]; }
    const const_iterator end() const { return &rows[n]; }

    reference operator[](const int& i) { return rows[i]; }
    const_reference operator[](const int& i) const { return rows[i]; }

    void for_each(std::function<void(Ty&)> lambda) const {
        for (size_type row = 0; row < n; ++row) {
            for (size_type cell = 0; cell < n; ++cell) {
                lambda(rows[row][cell]);
            }
        }
    }

    void for_each(
        std::function<void(Ty&, size_type&, size_type&)> lambda) const {
        for (size_type row = 0; row < n; ++row) {
            for (size_type cell = 0; cell < n; ++cell) {
                lambda(rows[row][cell], row, cell);
            }
        }
    }

    void iota(Ty start, std::unordered_set<Ty> avoid = {static_cast<Ty>(0)}) {
        this->for_each([&](Ty& element, size_type&, size_type&) {
            while (avoid.find(start) != avoid.end()) {
                ++start;
            }

            element = start++;
        });
    }

    void sort() {
        size_type item_count = 0;
        std::unique_ptr<Ty[]> listed_elements{std::make_unique<Ty[]>(total_n)};

        this->for_each([&](const Ty& element) {
            listed_elements[item_count++] = element;
        });

        std::sort(listed_elements.get(), listed_elements.get() + total_n);
        item_count = 0;

        this->for_each(
            [&](Ty& element) { element = listed_elements[item_count++]; });
    }

    template <class Function>
    void sort(Function func) {
        size_type item_count = 0;
        std::unique_ptr<Ty[]> listed_elements{std::make_unique<Ty[]>(total_n)};

        this->for_each([&](const Ty& element) {
            listed_elements[item_count++] = element;
        });

        std::sort(listed_elements.get(), listed_elements.get() + total_n, func);
        item_count = 0;

        this->for_each(
            [&](Ty& element) { element = listed_elements[item_count++]; });
    }

    void sort_rows() {
        for (size_type row = 0; row < n; ++row) {
            std::sort(rows[row].begin(), rows[row].end());
        }
    }

    template <class Function>
    void sort_rows(Function func) {
        for (size_type row = 0; row < n; ++row) {
            std::sort(rows[row].begin(), rows[row].end(), func);
        }
    }

    const void output(const bool& space = true) const {
        for (size_type row = 0; row < n; ++row) {
            for (size_type cell = 0; cell < n; ++cell) {
                std::cout << rows[row][cell];

                if (space && cell < n - 1) {
                    std::cout << ' ';
                }
            }

            std::cout << '\n';
        }
    }

   private:
    std::unique_ptr<row_type[]> rows;
    size_type n;
    size_type total_n;
};