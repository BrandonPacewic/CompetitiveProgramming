#include <algorithm>
#include <array>
#include <bits/stdint-intn.h>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
using namespace std;

//dbg
#ifdef DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() { cerr << endl; DBG_COUNT++; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
template<typename T_List> void testList(T_List List) { cerr << '#' << DBG_COUNT << " __LIST_ARGS__: ("; DBG_COUNT++; for (int i = 0; i < List.size(); i++) { cerr << List[i] << (i < List.size() - 1 ? ", " : ")\n"); } }
#define testArgs(...) cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", DBG_OUT(__VA_ARGS__)
#else
template<typename T_List> void testList(T_List List) { return; }
#define testArgs(...)
#endif


//modulo http://www.cplusplus.com/forum/general/19502/
template<typename T, typename OP> struct modulo { T bace; }; enum { mod };
template<typename T> modulo<T, decltype(mod)> operator<(const T& front, decltype(mod)) { return  { front }; }
template<typename T> T operator>(modulo<T, decltype(mod)> tail, T exponent) { T& bace = tail.bace; return bace % exponent < 0 ? (bace % exponent) + exponent : bace % exponent; }

const int64_t modVal = 1000000007;

void runCase(int tc) {
    int64_t R, C;
    cin >> R >> C;

    int64_t total = 0;

    for (int i = 1; i < R && i < C; i++) {
        total += (R - i) * (C - i) * i;
    }

    cout << "Case #" << tc << ": " << (total <mod> modVal) << '\n';
}


int main() {
#ifdef TEXT_IO
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cout << flush;
    }
}