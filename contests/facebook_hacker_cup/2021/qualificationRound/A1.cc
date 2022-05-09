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

const uint32_t INF = uint32_t(numeric_limits<int32_t>::max() / 2);

bool is_vowel(const char& ch) {
    const string vowels = "aeiou";
    return vowels.find(ch) != string::npos;
}

void run_case(const uint16_t& tc) {
    string S;
    cin >> S;

    uint32_t best = INF;
    bool opposing_nucleotides = false;

    for_each(S.begin(), S.end(), [&](const char& ch) {
        uint32_t cost = 0;

        for_each(S.begin(), S.end(), [&](const char& ch2) {
            if (ch2 == ch) return;

            if (is_vowel(ch) == is_vowel(ch2)) {
                cost += 2;
            } else {
                ++cost;
                opposing_nucleotides = true;
            }
        });

        best = min(cost, best);
    });

    best = min(best, (opposing_nucleotides ? INF : uint32_t(S.length())));
    cout << "Case #" << tc << ": " << best << '\n';
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