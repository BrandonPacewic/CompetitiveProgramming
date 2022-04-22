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
template<typename A, typename B> 
std::ostream& operator<<(std::ostream& os, const std::pair<A, B>& p) { 
    return os << '(' << p.first << ", " << p.second << ')'; 
}

// dbg output stream handling for containers excluding type std::string
template<typename T_container, typename T = typename std::enable_if<
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

//dbg
#ifdef DBG_MODE
void dbg_out() { std::cerr << std::endl; }
template<typename Head, typename... Tail> 
void dbg_out(Head A, Tail... B) { std::cerr << ' ' << A; dbg_out(B...); }
#define test(...) std::cerr << "[" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define test(...)
#endif


template<typename T_container>
void output_container(const T_container& container, const bool& space = true,
    const bool& new_line = true) {
    int start = 0;
    int end = int(container.size());

    for (int i = start; i < end; ++i) {
        std::cout << container[i];

        if (space && i < end - 1) std::cout << ' ';
    }

    std::cout << (new_line ? '\n' : ' ');
}

const int INF = int(1e9) + 5;
const int target = int(1e6);

void run_case(const int& tc) {
    array<array<int, 4>, 3> printers;

    for (auto& printer : printers)
        for (auto& cartrage : printer)
            cin >> cartrage;

    vector<int> min_cartrage(4, INF);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            min_cartrage[j] = min(min_cartrage[j], printers[i][j]);
        }
    }

    int extra = accumulate(min_cartrage.begin(), min_cartrage.end(), 0) - target;
    
    if (extra < 0) {
        cout << "Case #" << tc << ": IMPOSSIBLE" << '\n';
        return;
    }

    for (int i = 0; i < 4; ++i) {
        int remove = min(min_cartrage[i], extra);
        min_cartrage[i] -= remove;
        extra -= remove;
    }

    cout << "Case #" << tc << ": ";
    output_container(min_cartrage);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int test_cases;
    std::cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        run_case(tc);
        std::cout << std::flush;
    }

    return 0;
}