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


void runCase() {
    array<int, 3> A;
    cin >> A[0] >> A[1] >> A[2];

    if (A[0] - A[1] == A[1] - A[2]) {
        cout << "YES" << '\n';
        return;
    }

    bool ans = false;
    int64_t g1 = 2 * A[1] - A[2];
    int64_t g2 = 2 * A[1] - A[0];
    int64_t g3 = A[0] / 2 + A[2] / 2;

    if (g1 % A[0] == 0 && g1 > 0)
        ans = true;
    else if (g2 % A[2] == 0 && g2 > 0)
        ans = true;
    else if (g3 % A[1] == 0 && g3 > 0)
        ans = true;
    
    cout << (ans ? "YES" : "NO") << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        runCase();
        cout << flush;
    }
}
