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


void run_case(int tc) {
    using namespace std;
    //TODO: case code here

    cout << "Case #" << tc << ": " << '\n';
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int test_cases;
    std::cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        run_case(tc);
        std::cout << std::flush;
    }
}