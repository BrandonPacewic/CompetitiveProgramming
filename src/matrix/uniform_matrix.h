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

    template <class UnaryPredicate>
    bool any_of(UnaryPredicate predicate) const {
        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = (*it).begin(); jt != (*it).end(); ++jt) {
                if (predicate(*jt)) {
                    return true;
                }
            }
        }

        return false;
    }

    template <class UnaryPredicate>
    bool all_of(UnaryPredicate predicate) const {
        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = (*it).begin(); jt != (*it).end(); ++jt) {
                if (!predicate(*jt)) {
                    return false;
                }
            }
        }

        return true;
    }

    template <class UnaryPredicate>
    bool none_of(UnaryPredicate predicate) const {
        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = (*it).begin(); jt != (*it).end(); ++jt) {
                if (predicate(*jt)) {
                    return false;
                }
            }
        }

        return true;
    }

    template <typename ReturnValue = size_type>
    ReturnValue count(const value_type& value) const {
        ReturnValue count = 0;

        for (const_row_pointer it = begin(); it != end(); ++it) {
            for (type_const_pointer jt = (*it).begin(); jt != (*it).end();
                 ++jt) {
                if (*jt == value) {
                    ++count;
                }
            }
        }

        return count;
    }

    template <class UnaryPredicate, typename ReturnValue = size_type>
    ReturnValue count(UnaryPredicate predicate) const {
        ReturnValue count = 0;

        for (const_row_pointer it = begin(); it != end(); ++it) {
            for (type_const_pointer jt = (*it).begin(); jt != (*it).end();
                 ++jt) {
                if (predicate(*jt)) {
                    ++count;
                }
            }
        }

        return count;
    }

    void fill(const value_type& value) {
        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = it->begin(); jt != it->end(); ++jt) {
                *jt = value;
            }
        }
    }

    template <class UnaryPredicate>
    void fill(const value_type& value, UnaryPredicate predicate) {
        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = it->begin(); jt != it->end(); ++jt) {
                if (predicate(*jt)) {
                    *jt = value;
                }
            }
        }
    }

    template <class BinaryPredicate>
    void fill_if(const value_type& value, BinaryPredicate predicate) {
        for (size_type row = 0; row < row_length; ++row) {
            for (size_type cell = 0; cell < row_length; ++cell) {
                if (predicate(row, cell)) {
                    rows[row][cell] = value;
                }
            }
        }
    }

    type_pointer find_if(const value_type& target) {
        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = it->begin(); jt != it->end(); ++jt) {
                if (*jt == target) {
                    return jt;
                }
            }
        }

        return end()->end();
    }

    template <class UnaryPredicate>
    type_pointer find_if(UnaryPredicate predicate) {
        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = (*it).begin(); jt != (*it).end(); ++jt) {
                if (predicate(*jt)) {
                    return jt;
                }
            }
        }

        return end()->end();
    }

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

    void iota(value_type start) {
        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = (*it).begin(); jt != (*it).end(); ++jt) {
                *jt = start, ++start;
            }
        }
    }

    bool is_sorted() const {
        for (const_row_pointer it = begin(); it != end(); ++it) {
            for (type_const_pointer jt = (*it).begin(); jt != (*it).end();
                 ++jt) {
                if (jt != (*it).begin()) {
                    if (*jt < *(jt - 1)) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    template <class BinaryPredicate>
    bool is_sorted(BinaryPredicate predicate) const {
        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = (*it).begin(); jt != (*it).end(); ++jt) {
                if (jt != (*it).begin()) {
                    if (predicate(*jt, *(jt - 1))) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    const void output(const bool& space = true) const {
        for (size_type row = 0; row < row_length; ++row) {
            for (size_type cell = 0; cell < row_length; ++cell) {
                std::cout << rows[row][cell];

                if (space && cell < row_length - 1) {
                    std::cout << ' ';
                }
            }

            std::cout << '\n';
        }
    }

    const void output(std::ostream& os) const {
        for (size_type row = 0; row < row_length; ++row) {
            for (size_type cell = 0; cell < row_length; ++cell) {
                os << rows[row][cell];

                if (cell < row_length - 1) {
                    os << ' ';
                }
            }

            os << '\n';
        }
    }

    bool rows_sorted() const {
        for (const_row_pointer it = begin(); it != end(); ++it) {
            if (!std::is_sorted(it->begin(), it->end())) {
                return false;
            }
        }

        return true;
    }

    template <class BinaryPredicate>
    bool rows_sorted(BinaryPredicate predicate) const {
        for (const_row_pointer it = begin(); it != end(); ++it) {
            if (!std::is_sorted(it->begin(), it->end(), predicate)) {
                return false;
            }
        }

        return true;
    }

    void sort() {
        size_type item_count = 0;
        std::unique_ptr<value_type[]> listed_elements{
            std::make_unique<value_type[]>(this->total_size())};

        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = (*it).begin(); jt != (*it).end(); ++jt) {
                listed_elements[item_count] = *jt, ++item_count;
            }
        }

        std::sort(listed_elements.get(),
                  listed_elements.get() + this->total_size());
        item_count = 0;

        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = (*it).begin(); jt != (*it).end(); ++jt) {
                *jt = listed_elements[item_count], ++item_count;
            }
        }
    }

    template <class BinaryPredicate>
    void sort(BinaryPredicate predicate) {
        size_type item_count = 0;
        std::unique_ptr<value_type[]> listed_elements{
            std::make_unique<value_type[]>(this->total_size())};

        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = (*it).begin(); jt != (*it).end(); ++jt) {
                listed_elements[item_count] = *jt, ++item_count;
            }
        }

        std::sort(listed_elements.get(),
                  listed_elements.get() + this->total_size(), predicate);
        item_count = 0;

        for (row_pointer it = begin(); it != end(); ++it) {
            for (type_pointer jt = (*it).begin(); jt != (*it).end(); ++jt) {
                *jt = listed_elements[item_count], ++item_count;
            }
        }
    }

    void sort_rows() {
        for (row_pointer it = begin(); it != end(); ++it) {
            std::sort((*it).begin(), (*it).end());
        }
    }

    template <class BinaryPredicate>
    void sort_rows(BinaryPredicate predicate) {
        for (row_pointer it = begin(); it != end(); ++it) {
            std::sort((*it).begin(), (*it).end(), predicate);
        }
    }

   private:
    std::unique_ptr<row_type[]> rows;
    size_type row_length;
};