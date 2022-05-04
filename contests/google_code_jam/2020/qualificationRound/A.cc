#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

template <typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A, B>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

template <typename T_container,
          typename T = typename std::enable_if<
              !std::is_same<T_container, std::string>::value,
              typename T_container::value_type>::type>
std::ostream& operator<<(std::ostream& os, const T_container& container) {
    os << '{';
    std::string separator;

    for (const T& item : container) {
        os << separator << item, separator = ", ";
    }

    return os << '}';
}

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
class _uniform_matrix_row {
   public:
    typedef _Tp* iterator;
    typedef const _Tp* const_iterator;

    _uniform_matrix_row() {}

    _uniform_matrix_row(std::size_t _sz)
        : elements{std::make_unique<_Tp[]>(_sz)}, sz{_sz} {}

    _uniform_matrix_row(std::size_t _sz, const _Tp& _element)
        : elements{std::make_unique<_Tp[]>(_sz)}, sz{_sz} {
        std::fill(elements.get(), elements.get() + sz, _element);
    }

    const std::size_t size() const { return sz; }

    iterator begin() { return &elements[0]; }
    const const_iterator begin() const { return &elements[0]; }

    iterator end() { return &elements[sz]; }
    const const_iterator end() const { return &elements[sz]; }

    _Tp& operator[](const int& i) { return elements[i]; }

   private:
    std::unique_ptr<_Tp[]> elements;
    std::size_t sz;
};

template <typename _Tp>
class uniform_matrix {
   public:
    typedef _uniform_matrix_row<_Tp> row_type;
    typedef row_type* iterator;
    typedef const row_type* const_iterator;

    uniform_matrix(std::size_t _sz)
        : rows{std::make_unique<row_type[]>(_sz)}, sz{_sz} {
        for (std::size_t i = 0; i < sz; ++i) {
            rows[i] = _uniform_matrix_row<_Tp>(sz);
        }
    }

    uniform_matrix(std::size_t _sz, const _Tp& _element)
        : rows{std::make_unique<row_type[]>(_sz)}, sz{_sz} {
        for (std::size_t i = 0; i < sz; ++i) {
            rows[i] = row_type(sz, _element);
        }
    }

    const std::size_t size() const { return sz; }

    iterator begin() { return &rows[0]; }
    const const_iterator begin() const { return &rows[0]; }

    iterator end() { return &rows[sz]; }
    const const_iterator end() const { return &rows[sz]; }

    row_type& operator[](const int& i) const { return rows[i]; }

    void for_each(
        std::function<void(_Tp&, std::size_t&, std::size_t&)> lambda) const {
        for (std::size_t row = 0; row < sz; ++row) {
            for (std::size_t cell = 0; cell < sz; ++cell) {
                lambda(rows[row][cell], row, cell);
            }
        }
    }

    void iota(_Tp start,
              std::unordered_set<_Tp> avoid = {static_cast<_Tp>(0)}) {
        this->for_each([&](_Tp& element, std::size_t&, std::size_t&) {
            while (avoid.find(start) != avoid.end()) {
                ++start;
            }

            element = start++;
        });
    }

    void sort_rows(std::function<bool(_Tp&, _Tp&)> lambda = [](_Tp& a, _Tp& b) {
        return a < b;
    }) {
        for (std::size_t row = 0; row < sz; ++row) {
            std::sort(rows[row].begin(), rows[row].end(), lambda);
        }
    }

    const void output(const bool& space = false) const {
        for (std::size_t row = 0; row < sz; ++row) {
            for (std::size_t cell = 0; cell < sz; ++cell) {
                std::cout << rows[row][cell];

                if (space && cell < sz - 1) {
                    std::cout << ' ';
                }
            }

            std::cout << '\n';
        }
    }

   private:
    std::unique_ptr<row_type[]> rows;
    std::size_t sz;
};

void run_case(const uint16_t& tc) {
    uint16_t N;
    cin >> N;
    
    uniform_matrix<uint16_t> matrix(N);

    matrix.for_each([&](uint16_t& item, auto&, auto&) { cin >> item; });

    uint32_t k = 0;

    for (uint16_t i = 0; i < N; ++i) {
        k += matrix[i][i];
    }

    uint32_t r = 0, c = 0;
    vector<unordered_set<uint16_t>> used_rows(N), used_cols(N);
    vector<bool> changed_rows(N, false), changed_cols(N, false);

    for (uint16_t i = 0; i < N; ++i) {
        for (uint16_t j = 0; j < N; ++j) {
            if (used_rows[i].count(matrix[i][j]) && !changed_rows[i]) {
                changed_rows[i] = true;
                ++r;
            } else {
                used_rows[i].insert(matrix[i][j]);
            }

            if (used_cols[j].count(matrix[i][j]) && !changed_cols[j]) {
                changed_cols[j] = true;
                ++c;
            } else {
                used_cols[j].insert(matrix[i][j]);
            }
        }
    }

    cout << "Case #" << tc << ": " << k << ' ' << r << ' ' << c << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t test_cases;
    std::cin >> test_cases;

    for (uint16_t tc = 1; tc <= test_cases; tc++) {
        run_case(tc);
#ifdef DBG_MODE
        std::cout << std::flush;
#endif
    }

#ifndef DBG_MODE
    std::cout << std::flush;
#endif

    return 0;
}