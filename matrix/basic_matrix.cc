/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * basic_matrix.cc
 */

#include <cstddef>
#include <iostream>
#include <stdexcept>

template<typename _Tp, const std::size_t _Sz>
struct _basic_matrix_row {
    _Tp* elements;
    int current_cell_index;

    _basic_matrix_row() : elements{new _Tp[_Sz]}, current_cell_index{0} {}
    ~_basic_matrix_row() { delete[] elements; };

    _Tp& operator[](const int& index) { return elements[index]; }

    int assign_back(const _Tp& new_element) try {
        elements[current_cell_index] = new_element;
        ++current_cell_index;
    }
    catch (const std::out_of_range& error) {
        std::cerr << "assign_back has no elements to assign" << '\n';
        throw error;
    }
};

template<typename _Tp, const std::size_t _Sz>
struct basic_matrix {
    _basic_matrix_row<_Tp,_Sz>* rows;
    int current_row_index;

    basic_matrix() : 
        rows{new _basic_matrix_row<_Tp, _Sz>[_Sz]}, current_row_index{0} {}
    
    ~basic_matrix() { delete[] rows; }

    _basic_matrix_row<_Tp, _Sz>& operator[](const int& index) 
    { return rows[index]; }

    void assign_back(const _Tp& new_element) try {
        int current = rows[current_row_index].assign_back(new_element);

        if (current == _Sz) { ++current_row_index; }
    }
    catch (const std::out_of_range& error) {
        std::cerr << "assign_back has no rows to assign" << '\n';
        throw error;
    }
};