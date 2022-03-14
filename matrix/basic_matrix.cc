/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * basic_matrix.cc
 */

// This basic matrix is almost identical to uniform_matrix, just renamed so 
// I can search for the version of this type that contains all the definitions
// in one file so I can quickly fnid it while in a contest

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

template<typename _Tp>
struct _basic_matrix_row : public std::vector<_Tp> {
    int current_cell_index = 0;

    int assign_back(const _Tp& new_element) try {
        *this[current_cell_index] = new_element;
        ++current_cell_index;

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

    basic_matrix(std::size_t _sz) 
        : rows{new _basic_matrix_row<_Tp>[_sz]}, current_row_index{0}, 
        sz{_sz} {}

    basic_matrix(std::size_t _sz, _Tp inital)
        : rows{new _basic_matrix_row<_Tp>[_sz]}, current_row_index{0},
        sz{_sz} {}

    ~basic_matrix() { delete[] rows; }

    const std::size_t size() const noexcept { return sz; }

    const _basic_matrix_row<_Tp>& operator[](
        const int& index) const noexcept { return rows[index]; }

    void assign_back(const _Tp& new_element) try {
        int current = rows[current_row_index].assign_back(new_element);

        if (current == sz) { ++current_row_index; }
    }
    catch (const std::out_of_range& error) {
        std::cerr << "assign_back has no rows to assign" << '\n';
        throw error;
    }

    template<class _Fun>
    void for_all(_Fun function) const noexcept {
        for (int _row = 0; _row < sz; ++_row) {
            for (int _cell = 0; _cell < sz; ++_cell) {
                function(*this[_row][_cell], _row, _cell);
            }
        }
    }
};
