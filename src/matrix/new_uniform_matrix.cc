#include <cstddef>
#include <functional>
#include <memory>
#include <iostream>

template<typename _Tp>
class _uniform_matrix_row {
public:
    typedef _Tp*       iterator;
    typedef const _Tp* const_iterator;

    _uniform_matrix_row() {}

    _uniform_matrix_row(std::size_t _sz) 
            : elements{std::make_unique<_Tp[]>(_sz)}, 
            sz{_sz}, current_cell_index{0} {}

    const std::size_t size() const { return sz; }

    iterator begin() { return &elements[0]; }
    const const_iterator begin() const { return &elements[0]; }

    iterator end() { return &elements[sz - 1]; }
    const const_iterator end() const { return &elements[sz - 1]; }

    _Tp& operator[](int i) { return elements[i]; }

    int assign_back(const _Tp& new_element) {
        elements[current_cell_index++] = new_element;
        return current_cell_index;
    }

private:
    std::unique_ptr<_Tp[]> elements;
    std::size_t sz;
    int current_cell_index;
};

template<typename _Tp>
class uniform_matrix {
public:
    typedef _uniform_matrix_row<_Tp> row_type;
    typedef row_type*              iterator;
    typedef const row_type*        const_iterator;

    uniform_matrix(std::size_t _sz) 
            : rows{std::make_unique<row_type[]>(_sz)}, 
            sz{_sz}, current_row_index{0} {
        for (int i = 0; i < int(sz); ++i) {
            rows[i] = _uniform_matrix_row<_Tp>(sz);
        }
    }

    const std::size_t size() const { return sz; }
    
    iterator begin() { return &rows[0]; }
    const const_iterator begin() const { return &rows[0]; }

    iterator end() { return &rows[sz - 1]; }
    const const_iterator end() const { return &rows[sz - 1]; }

    row_type& operator[](int index) const { return rows[index]; }

    void assign_back(const _Tp& new_element) {
        int current = rows[current_row_index].assign_back(new_element);

        if (current == sz) { 
            ++current_row_index; 
        }
    }

    void for_each(std::function<void(_Tp&)> lambda) const {
        for (int i = 0; i < int(sz); ++i) {
            for (int j = 0; j < int(sz); ++j) {
                lambda(rows[i][j]);
            }
        }
    }

    const void output(const bool& space = false) const {
        for (std::size_t row = 0; row < sz; ++row) {
            for (std::size_t cell = 0; cell < sz; ++cell) {
                std::cout << rows[row][cell];

                if (space && cell < int(sz) - 1) {
                    std::cout << ' ';
                }
            }
        }

        std::cout << '\n';
    }

private:
    std::unique_ptr<row_type[]> rows;
    std::size_t sz;
    int current_row_index;
};