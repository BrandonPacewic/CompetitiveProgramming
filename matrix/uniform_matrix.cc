/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * uniform_matrix.cc
 */

#include <cstddef>
#include <iostream>
#include <functional>
#include <stdexcept>

template<typename _Tp>
struct _basic_matrix_row {
    _Tp* elements;
    std::size_t sz;
    int current_cell_index;

    _basic_matrix_row() {}

    _basic_matrix_row(std::size_t _size) 
        : elements{new _Tp[_size]}, sz{_size}, current_cell_index{0} {}

    ~_basic_matrix_row() { delete[] elements; }

    std::size_t size() const noexcept { return sz; }

    _Tp& operator[](int index) { return elements[index]; }

    int assign_back(const _Tp& new_element) try {
        elements[current_cell_index++] = new_element;
        return current_cell_index;
    }
    catch (const std::out_of_range& error) {
        std::cerr << "assign_back has no cell to assign" << '\n';
        throw error;
    }
};

template<typename _Tp>
struct basic_matrix {
    _basic_matrix_row<_Tp>* rows;
    std::size_t sz;
    int current_row_index;

    basic_matrix(std::size_t _size) 
        : rows{new _basic_matrix_row<_Tp>[_size]}, sz{_size},
        current_row_index{0} { 
        for (int i = 0; i < int(sz); ++i) {
            rows[i] = _basic_matrix_row<_Tp>(sz);
        }
    }

    std::size_t size() const { return sz; }

    _basic_matrix_row<_Tp>& operator[](int index) const { return rows[index]; }

    void assign_back(const _Tp& new_element) try {
        int current = rows[current_row_index].assign_back(new_element);

        if (current == sz) { 
            ++current_row_index; 
        }
    }
    catch (const std::out_of_range& error) {
        std::cerr << "assign_back has no rows to assign" << '\n';
        throw error;
    }

    void for_all(std::function<void(_Tp, int, int)> lambda) const {
        for (int _row = 0; _row < int(sz); ++_row) {
            for (int _cell = 0; _cell < int(sz); ++_cell) {
                lamdba(rows[_row][_cell], _row, _cell);
            }
        }
    }

    const void output(std::ostream& os = std::cout, 
        const bool& space = false) const {
        for (int row = 0; row < int(sz); ++row) {
            for (int cell = 0; cell < int(sz); ++cell) {
                os << rows[row][cell];

                if (space && cell < int(sz) - 1) {
                    os << ' ';
                }
            }
        }

        os << '\n';
    }
};

