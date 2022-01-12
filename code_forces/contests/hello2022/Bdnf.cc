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

#ifdef DBG_MODE
template<typename T_Vector> void testListInList(T_Vector List) { cerr << '#' << DBG_COUNT << " __LIST_ARGS__:("; DBG_COUNT++; for (int i = 0; i < List.size(); i++) { cerr << '('; for (int k = 0; k < List[i].size(); k++) cerr << List[i][k] << (k < List[i].size() - 1 ? ", " : ")"); cerr << (i < List.size() - 1 ? ", " : ")\n"); } }
#else
template<typename T_Vector> void testListInList(T_Vector List) { return; }
#endif


void runCase() {
    int N;
    cin >> N;
    vector<array<int, 4>> seg(N);

    for (auto &nseg : seg) {
        cin >> nseg[0] >> nseg[1] >> nseg[2];
        nseg[3] = nseg[1] - nseg[0];
    }

    testListInList(seg);
    vector<int> totals(N);

    for (int i = 0; i < N; i++) {

    }
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
