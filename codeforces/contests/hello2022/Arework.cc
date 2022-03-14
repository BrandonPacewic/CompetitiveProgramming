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
template<typename A, typename B> 
std::ostream& operator<<(std::ostream& os, const std::pair<A, B>& p) { 
    return os << '(' << p.first << ", " << p.second << ')'; 
}

// dbg output stream handling for containers excluding type std::string
template<typename T_container, typename T = typename std::enable_if<
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

//dbg
#ifdef DBG_MODE
void dbg_out() { std::cerr << std::endl; }
template<typename Head, typename... Tail> 
void dbg_out(Head A, Tail... B) { std::cerr << ' ' << A; dbg_out(B...); }
#define test(...) std::cerr << "[" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define test(...)
#endif

template<typename _Tp, std::size_t _Sz>
struct _basic_matrix_row {
    _Tp* elements;
    int current_cell_index;

    _basic_matrix_row() : elements{new _Tp[_Sz]}, current_cell_index{0} {}
    ~_basic_matrix_row() { delete[] elements; };

    const std::size_t size() const noexcept { return _Sz; }
    
    const _Tp& operator[](const int& index) const noexcept 
    { return elements[index]; }

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

    const std::size_t size() const noexcept { return _Sz; }

    const _basic_matrix_row<_Tp, _Sz>& operator[](
        const int& index) const noexcept { return rows[index]; }

    void assign_back(const _Tp& new_element) try {
        int current = rows[current_row_index].assign_back(new_element);

        if (current == _Sz) { ++current_row_index; }
    }
    catch (const std::out_of_range& error) {
        std::cerr << "assign_back has no rows to assign" << '\n';
        throw error;
    }

    template<class _Fun>
    void for_all(_Fun function) noexcept {
        for (int row = 0; row < _Sz; ++row) {
            for (int cell = 0; cell < _Sz; ++cell) {
                function(*this[row][cell], row, cell);
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

    // basic_matrix<char, K> matrix;
    int current = 0, count = 0;

    cout << '\n';
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