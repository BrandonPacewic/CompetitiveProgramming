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
        typename T_container::value_type>::type> std::ostream& operator<<(
            std::ostream& os, const T_container& A) { 
    std::string sep; 
    os << '{';

    for (const T& a : A) { 
        os << sep << a, sep = ", ";
    }

    return os << '}'; 
}

//dbg
#ifdef DBG_MODE
int64_t _dbg_count = 0;
void _dbg_count() { std::cerr << std::endl; ++_dbg_count; }
template<typename Front, typename... Back> 
void _dbg_count(Head A, Tail... B) { std::cerr << ' ' << A; _dbg_count(B...); }
#define test(...) std::cerr << '#' << _dbg_count << 
    " [" << #__VA_ARGS__ << "]:", _dbg_count(__VA_ARGS__)
#else
#define test(...)
#endif


void run_case(int tc) {
    using namespace std;
    //TODO: case code here

    cout << "Case #" << tc << ": " << '\n';
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
}