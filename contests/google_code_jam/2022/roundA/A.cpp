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

template <typename T, typename T_iterable>
std::vector<std::pair<T, uint16_t>> run_length_encoding(
    const T_iterable& items) {
    std::vector<std::pair<T, uint16_t>> encoding;
    T previous_item;
    uint16_t current_count = 0;

    std::for_each(items.begin(), items.end(), [&](const T& item) {
        if (item == previous_item) {
            ++current_count;
        } else {
            if (current_count) {
                encoding.emplace_back(previous_item, current_count);
            }

            previous_item = item;
            current_count = 1;
        }
    });

    if (current_count) {
        encoding.emplace_back(previous_item, current_count);
    }

    return encoding;
}

void run_case(const uint16_t& tc) {
    string S;
    cin >> S;

    auto occurrences = run_length_encoding<char>(S);

    cout << "Case #" << tc << ": ";

    auto output = [](const pair<char, uint16_t>& a) -> void {
        for (uint16_t i = 0; i < a.second; ++i) {
            cout << a.first;
        }
    };

    auto output_double = [](const pair<char, uint16_t>& a) -> void {
        for (uint16_t i = 0; i < a.second; ++i) {
            cout << a.first << a.first;
        }
    };

    for (auto i = occurrences.begin(); i != occurrences.end() - 1; ++i) {
        if (i->first < (i + 1)->first) {
            output_double(*i);
        } else {
            output(*i);
        }
    }

    output(occurrences.back());
    cout << '\n';
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