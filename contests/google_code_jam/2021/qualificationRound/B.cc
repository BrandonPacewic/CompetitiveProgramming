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
#include <memory>
#include <numeric>
#include <limits>
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

const int INF = int(numeric_limits<int>::max() / 2);

void run_case(const uint16_t& tc) {
    int X, Y;
    string S;
    cin >> X >> Y >> S;
    int end_c = (S[0] == '?' || S[0] == 'C') ? 0 : INF;
    int end_j = (S[0] == '?' || S[0] == 'J') ? 0 : INF;

    for_each(S.begin() + 1, S.end(), [&](const char& ch) {
        int nend_c = (ch == '?' || ch == 'C') ? min(end_j + Y, end_c) : INF;
        int nend_j = (ch == '?' || ch == 'J') ? min(end_j, end_c + X) : INF;
        end_c = nend_c;
        end_j = nend_j;
    });

    cout << "Case #" << tc << ": " << min(end_c, end_j) << '\n';
}

int main() {
    test(INF);
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