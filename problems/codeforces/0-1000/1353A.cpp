// #include <algorithm>
// #include <array>
// #include <cassert>
// #include <chrono>
// #include <cmath>
// #include <cstring>
// #include <functional>
// #include <iomanip>
// #include <iostream>
// #include <map>
// #include <numeric>
// #include <queue>
// #include <random>
// #include <set>
// #include <unordered_map>
// #include <vector>
// using namespace std;

// // dbg
// #ifdef DBG_MODE
// int64_t DBG_COUNT = 0;
// void DBG_OUT() {
//     cerr << endl;
//     DBG_COUNT++;
// }
// template <typename Front, typename... Back>
// void DBG_OUT(Front K, Back... T) {
//     cerr << ' ' << K;
//     DBG_OUT(T...);
// }
// template <typename T_List>
// void testList(T_List List) {
//     cerr << '#' << DBG_COUNT << " __LIST_ARGS__: (";
//     DBG_COUNT++;
//     for (int i = 0; i < List.size(); i++) {
//         cerr << List[i] << (i < List.size() - 1 ? ", " : ")\n");
//     }
// }
// #define testArgs(...)                                                     \
//     cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", \
//         DBG_OUT(__VA_ARGS__)
// #else
// template <typename T_List>
// void testList(T_List List) {
//     return;
// }
// #define testArgs(...)
// #endif

// void runCase() {
//     int N, M;
//     cin >> N >> M;

//     cout << min(2, N - 1) * M << '\n';
// }

// int main() {
// #ifdef TEXT_IO
//     freopen("in.txt", "r", stdin);
//     freopen("ou.txt", "w", stdout);
// #endif

//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int test_cases;
//     cin >> test_cases;

//     while (test_cases--) {
//         runCase();
//         cout << flush;
//     }
// }

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

void run_case() {
    uint16_t N, M;
    cin >> N >> M;

    uint16_t ans = min(2, N - 1) * M;
    cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t test_cases;
    std::cin >> test_cases;

    while (test_cases--) {
        run_case();
#ifdef DBG_MODE
        std::cout << std::flush;
#endif
    }

#ifndef DBG_MODE
    std::cout << std::flush;
#endif

    return 0;
}