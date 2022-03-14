/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * basic_matrix.cc
 */

// This basic matrix is almost identical to uniform_matrix, just renamed so 
// I can search for the version of this type that contains all the definitions
// in one file so I can quickly fnid it while in contest

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

template<typename _Tp>
struct _basic_matrix_row {
    _Tp* elements;
    std::size_t sz;
    int current_cell_index;

    _basic_matrix_row() { }

    _basic_matrix_row(std::size_t _size) 
        : elements{new _Tp[_size]}, sz{_size}, current_cell_index{0} { }

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
        for (int i = 0; i < int(sz); i++) {
            rows[i] = _basic_matrix_row<_Tp>(sz);
        }
    }

    std::size_t size() const noexcept { return sz; }

    _basic_matrix_row<_Tp>& operator[](int index) const { return rows[index]; }

    void assign_back(const _Tp& new_element) try {
        int current = rows[current_row_index].assign_back(new_element);

        if (current == sz) { ++current_row_index; }
    }
    catch (const std::out_of_range& error) {
        std::cerr << "assign_back has no rows to assign" << '\n';
        throw error;
    }

    // TODO: lambda function should have type of void
    template<class _Fun>
    void for_all(_Fun function) const noexcept {
        for (int _row = 0; _row < int(sz); ++_row) {
            for (int _cell = 0; _cell < int(sz); ++_cell) {
                function(rows[_row][_cell], _row, _cell);
            }
        }
    }
};

