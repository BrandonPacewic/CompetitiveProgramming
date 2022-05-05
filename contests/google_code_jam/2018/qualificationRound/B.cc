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
    int N;
    cin >> N;
    array<vector<int>, 2> A;

    for (int i = 0; i < N; ++i) {
        int k;
        cin >> k;

        A[i % 2].push_back(k);
    }

    sort(A[0].begin(), A[0].end());
    sort(A[1].begin(), A[1].end());

    vector<int> ans;

    for (int i = 0; i < (N % 2 == 0) ? N / 2 : (N - 1) / 2; ++i) {
        ans.push_back(A[0][i]);
        ans.push_back(A[1][i]);
    }

    if (N % 2 != 0) ans.push_back(A[0][N - 1]);

    for_each(ans.begin(), ans.end() - 1, [&](const int& x, const auto& i) {
        if (x > ans[i + 1]) {
            cout << "Case #" << tc << ": " << i << '\n';
            return;
        }
    });

    cout << "Case #" << tc << ": OK" << '\n';
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