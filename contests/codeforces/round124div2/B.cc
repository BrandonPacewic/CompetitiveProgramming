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

template <typename T_iterable>
void print_iterable(const T_iterable& _iterable, const bool _space = true,
                    const bool _new_line = true, int _start = -1,
                    int _end = -1) {
    if (_start == -1) _start = 0;
    if (_end == -1) _end = int(_iterable.size());

    for (int i = _start; i < _end; i++) {
        std::cout << _iterable[i];

        if (_space && i < _end - 1) std::cout << ' ';
    }

    if (_new_line)
        std::cout << '\n';
    else
        std::cout << ' ';
}

const int64_t LIMIT = int64_t(10e9);

void run_case() {
    using namespace std;
    int N;
    cin >> N;

    vector<int64_t> ans;

    for (int64_t i = 1; i < LIMIT; i = (i * 3) + 1) {
        ans.push_back(i);

        if (int(ans.size()) == N) {
            break;
        }
    }

    if (int(ans.size()) != N) {
        cout << "NO" << '\n';
        return;
    }

    cout << "YES" << '\n';
    print_iterable(ans);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int test_cases;
    std::cin >> test_cases;

    while (test_cases--) {
        run_case();
        std::cout << std::flush;
    }

    return 0;
}