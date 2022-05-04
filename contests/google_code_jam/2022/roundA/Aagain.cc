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
#include <numeric>
#include <queue>
#include <set>
#include <vector>
using namespace std;

// dbg output stream handling for pairs
template <typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A, B>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

// dbg output stream handling for containers excluding type std::string
template <typename T_container,
          typename T = typename std::enable_if<
              !std::is_same<T_container, std::string>::value,
              typename T_container::value_type>::type>
std::ostream& operator<<(std::ostream& os, const T_container& A) {
    std::string sep;
    os << '{';

    for (const T& a : A) {
        os << sep << a, sep = ", ";
    }

    return os << '}';
}

// dbg
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
std::vector<std::pair<T, int>> run_length_encoding(const T_iterable& items) {
    std::vector<std::pair<T, int>> encoding;
    T previous;
    int count = 0;

    for (const T& item : items)
        if (item == previous) {
            count++;
        } else {
            if (count > 0) {
                encoding.emplace_back(previous, count);
            }

            previous = item;
            count = 1;
        }

    if (count > 0) {
        encoding.emplace_back(previous, count);
    }

    return encoding;
}

void run_case(const int& tc) {
    string S;
    cin >> S;
    auto occurrences = run_length_encoding<char>(S);

    cout << "Case #" << tc << ": ";

    auto output = [](const pair<char, int>& a) -> void {
        for (int i = 0; i < a.second; ++i) cout << a.first;
    };

    auto output_double = [](const pair<char, int>& a) -> void {
        for (int i = 0; i < a.second * 2; ++i) cout << a.first;
    };

    for (int i = 0; i < int(occurrences.size()) - 1; ++i) {
        if (occurrences[i].first < occurrences[i + 1].first) {
            output_double(occurrences[i]);
        } else
            output(occurrences[i]);
    }

    output(occurrences.back());
    cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int test_cases;
    std::cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        run_case(tc);
#ifdef DBG_MODE
        std::cout << std::flush;
#endif
    }

    return 0;
}