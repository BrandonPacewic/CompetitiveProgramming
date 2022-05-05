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
    uint32_t D;
    string S;
    cin >> D >> S;

    if (count(S.begin(), S.end(), 'S') > D) {
        cout << "Case #" << tc << ": IMPOSSIBLE" << '\n';
        return;
    }

    auto count_damage = [&](string S) -> uint32_t {
        int damage = 0, charge = 1;

        for_each(S.begin(), S.end(), [&](const char& ch) {
            if (ch == 'S') {
                damage += charge;
            } else {
                charge *= 2;
            }
        });

        return damage;
    };

    uint32_t swaps = 0;

    while (D < count_damage(S)) {
        for (uint16_t i = uint16_t(S.length()) - 1; i >= 0; --i) {
            if (S[i - 1] == 'C' && S[i] == 'S') {
                swap(S[i - 1], S[i]);
                ++swaps;
                break;
            }
        }
    }

    cout << "Case #" << tc << ": " << swaps << '\n';
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