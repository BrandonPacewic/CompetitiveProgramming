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

void run_case(const uint16_t& tc) {
    uint32_t R, C;
    cin >> R >> C;

    vector<vector<uint32_t>> M(R, vector<uint32_t>(C));

    for_each(M.begin(), M.end(), [&](auto& row) {
        for_each(row.begin(), row.end(), [&](auto& cell) { cin >> cell; });
    });

    vector<vector<uint32_t>> left(R, vector<uint32_t>(C, 0)),
        right(R, vector<uint32_t>(C, 0));
    vector<vector<uint32_t>> up(R, vector<uint32_t>(C, 0)),
        down(R, vector<uint32_t>(C, 0));

    for (uint32_t r = 0; r < R; ++r) {
        for (uint32_t c = 0; c < C; ++c) {
            if (M[r][c]) {
                left[r][c] = (c > 0) ? left[r][c - 1] : 0;
                up[r][c] = (r > 0) ? up[r - 1][c] : 0;
            } else {
                left[r][c] = 0;
                up[r][c] = 0;
            }
        }
    }

    for (uint32_t r = R - 1; r >= 0; --r) {
        for (uint32_t c = C - 1; c >= 0; --c) {
            if (M[r][c]) {
                right[r][c] = (c < C - 1) ? right[r][c + 1] : 0;
                down[r][c] = (r < R - 1) ? down[r + 1][c] : 0;
            } else {
                right[r][c] = 0;
                down[r][c] = 0;
            }
        }
    }

    uint32_t total = 0;

    for (uint32_t r = 0; r < R; ++r) {
        for (uint32_t c = 0; c < C; ++c) {
            total += max<uint32_t>(min(left[r][c], up[r][c] / 2) - 1, 0);
            total += max<uint32_t>(min(up[r][c], right[r][c] / 2) - 1, 0);
            total += max<uint32_t>(min(right[r][c], down[r][c] / 2) - 1, 0);
            total += max<uint32_t>(min(down[r][c], left[r][c] / 2) - 1, 0);

            total += max<uint32_t>(min(up[r][c], left[r][c] / 2) - 1, 0);
            total += max<uint32_t>(min(right[r][c], up[r][c] / 2) - 1, 0);
            total += max<uint32_t>(min(down[r][c], right[r][c] / 2) - 1, 0);
            total += max<uint32_t>(min(left[r][c], down[r][c] / 2) - 1, 0);
        }
    }

    cout << "Case #" << tc << ": " << total << '\n';
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