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

const int32_t INF = int32_t(numeric_limits<int32_t>::max());
const int32_t target = int32_t(1e6);
const uint8_t printer_count = 3;
const uint8_t cartridge_count = 4;

void run_case(const uint16_t& tc) {
    array<array<int32_t, 4>, 3> printers;

    for_each(printers.begin(), printers.end(), [&](auto& printer) {
        for_each(printer.begin(), printer.end(),
                 [&](auto& cartridge) { cin >> cartridge; });
    });

    vector<int32_t> min_cartridge(cartridge_count, INF);

    for (uint8_t i = 0; i < printer_count; ++i) {
        for (uint8_t j = 0; j < cartridge_count; ++j) {
            min_cartridge[j] = min(min_cartridge[j], printers[i][j]);
        }
    }

    int32_t extra =
        accumulate(min_cartridge.begin(), min_cartridge.end(), 0) - target;

    if (extra < 0) {
        cout << "Case #" << tc << ": IMPOSSIBLE" << '\n';
        return;
    }

    for (uint16_t i = 0; i < cartridge_count; ++i) {
        int32_t remove = min(min_cartridge[i], extra);
        min_cartridge[i] -= remove;
        extra -= remove;
    }

    cout << "Case #" << tc << ": ";
    output_container(min_cartridge);
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