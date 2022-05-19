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

template <typename T, class Fun>
void print_empty_matrix(const int& _x, const int& _y, T a, T b, Fun condition,
                        const bool& space = false) {
    for (int x = 0; x < _x; x++) {
        for (int y = 0; y < _y; y++) {
            std::cout << (condition(x, y) ? b : a);

            if (space) {
                std::cout << ' ';
            }
        }

        std::cout << '\n';
    }
}

void run_case(const uint16_t& tc) {
    uint32_t N;
    cin >> N;
    string A, B;
    cin >> A >> B;

    cout << "Case #" << tc << ":\n";

    print_empty_matrix(N, N, 'N', 'Y', [&](int x, int y) -> bool {
        if (x == y) return true;

        uint32_t starting = min(x, y), ending = max(x, y);
        bool conecting = B[x] == 'Y' && A[y] == 'Y';

        for (uint32_t i = starting + 1; i < ending; ++i) {
            conecting = conecting && A[i] == 'Y' && B[i] == 'Y';
        }

        return conecting;
    });
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