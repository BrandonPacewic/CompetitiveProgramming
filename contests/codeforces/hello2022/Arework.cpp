#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <vector>

// dbg output stream handling for pairs
template <typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A, B>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

// dbg output stream handling for containers excluding type std::string
template <typename T_container,
          typename T = typename std::enable_if<
              !std::is_same<T_container, std::string>::value,
              typename T_container::value_type>::type>
std::ostream& operator<<(std::ostream& os, const T_container& A) {
    std::string sep;
    os << '{';

    for (const T& a : A) {
        os << sep << a, sep = ", ";
    }

    return os << '}';
}

// dbg
#ifdef DBG_MODE
void dbg_out() { std::cerr << std::endl; }
template <typename Head, typename... Tail>
void dbg_out(Head A, Tail... B) {
    std::cerr << ' ' << A;
    dbg_out(B...);
}
#define test(...) std::cerr << "[" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define test(...)
#endif

template <typename _Tp>
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
    } catch (const std::out_of_range& error) {
        std::cerr << "assign_back has no cell to assign" << '\n';
        throw error;
    }
};

template <typename _Tp>
struct basic_matrix {
    _basic_matrix_row<_Tp>* rows;
    std::size_t sz;
    int current_row_index;

    basic_matrix(std::size_t _size)
        : rows{new _basic_matrix_row<_Tp>[_size]},
          sz{_size},
          current_row_index{0} {
        for (int i = 0; i < int(sz); i++) {
            rows[i] = _basic_matrix_row<_Tp>(sz);
        }
    }

    std::size_t size() const noexcept { return sz; }

    _basic_matrix_row<_Tp>& operator[](int index) const { return rows[index]; }

    void assign_back(const _Tp& new_element) try {
        int current = rows[current_row_index].assign_back(new_element);

        if (current == sz) {
            ++current_row_index;
        }
    } catch (const std::out_of_range& error) {
        std::cerr << "assign_back has no rows to assign" << '\n';
        throw error;
    }

    template <class _Fun>
    void for_all(_Fun function) const noexcept {
        for (int _row = 0; _row < int(sz); ++_row) {
            for (int _cell = 0; _cell < int(sz); ++_cell) {
                test(_row, _cell);
                function(rows[_row][_cell], _row, _cell);
            }
        }
    }
};

void run_case() {
    using namespace std;
    int K, N;
    cin >> K >> N;

    for (int i = 0, r = 1; i < N; ++i, r += 2) {
        if (r > K) {
            cout << -1 << '\n';
            return;
        }
    }

    basic_matrix<char> matrix(K);

    int cell = 0, count = 0;
    matrix.for_all([&](char& item, int y, int x) -> void {
        if (x == cell && y == cell && count < N) {
            ++count;
            cell += 2;
            item = 'R';
        } else {
            item = '.';
        }
    });

    matrix.for_all([&](char& item, int row, int col) -> void {
        cout << item;

        if (col >= K - 1) cout << '\n';
    });
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int test_cases;
    std::cin >> test_cases;

    while (--test_cases) {
        run_case();
        std::cout << std::flush;
    }

    return 0;
}