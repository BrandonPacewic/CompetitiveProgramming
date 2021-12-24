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

#ifndef TEST_SET
#define TEST_SET
#ifdef DBG_MODE
template<typename T_SET> void testSet(T_SET SET) { cerr << '#' << DBG_COUNT << " __SET_ARGS__: ( "; DBG_COUNT++; for (auto ch : SET) cerr << ch << ' '; cerr << ")\n"; }
#else
template<typename T_SET> void testSet(T_SET SET) { return; }
#endif
#endif


void runCase() {
    int lower, upper;
    cin >> lower >> upper;
    int count = 0;

    for (int i = lower + 1; i <= upper; i++) {
        for (int j = i + 1; j <= upper; j++) {
            if ((i & j) == 0)
                count++;
        }
    }

    cout << count << '\n';
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

    while (test_cases--) {
        runCase();
        cout << flush;
    }
}