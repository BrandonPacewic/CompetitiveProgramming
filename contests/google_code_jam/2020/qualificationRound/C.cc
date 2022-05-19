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

struct event {
    uint8_t start_time, end_time;
    uint16_t index;
};

void run_case(const uint16_t& tc) {
    int N;
    cin >> N;
    vector<event> events(N);

    for_each(events.begin(), events.end(), [&](event& e, const uint16_t& i) {
        cin >> e.start_time >> e.end_time;
        e.index = i;
    });

    sort(events.begin(), events.end(), [](const event& a, const event& b) {
        return a.start_time < b.start_time;
    });

    int end_c = -1, end_j = -1;
    string ans(N, '?');

    for_each(events.begin(), events.end(), [&](const event& e) {
        if (e.start_time <= end_c) {
            ans[e.index] = 'C';
            end_c = e.end_time;
        } else if (e.start_time <= end_j) {
            ans[e.index] = 'J';
            end_j = e.end_time;
        } else {
            cout << "Case #" << tc << ": "
                 << "IMPOSSIBLE" << '\n';
            return;
        }
    });

    cout << "Case #" << tc << ": " << ans << '\n';
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