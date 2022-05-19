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

template <typename T_container>
void output_container(const T_container& container, const bool space = true,
                      const bool new_line = true) {
    for (std::size_t i = 0; i < container.size(); ++i) {
        std::cout << container[i];

        if (space && i < container.size() - 1) {
            std::cout << ' ';
        }
    }

    std::cout << (new_line ? '\n' : ' ');
}

void run_case(const uint16_t& tc) {
    uint16_t N;
    string S;
    cin >> N >> S;

    vector<uint16_t> counts(N, 1);

    for_each(S.begin(), S.end(), [&](const char& ch, const auto& i) {
        for (uint16_t k = i; k > 0; --k) {
            if (!(S[k] - '0' > S[k - 1] - '0')) {
                break;
            }

            ++counts[i];
        }
    });

    cout << "Case #" << tc << ": ";
    output_container(counts);
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