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
    int N;
    cin >> N;
    vector<array<int, 3>> segs(N);

    for (auto &seg : segs)
        cin >> seg[0] >> seg[1] >> seg[2];

    for (int s = 1; s <= N; s++) {
        int min_index = segs[0][0], max_index = segs[0][1];

        for (int i = 1; i < s; i++) {
            if (segs[i][0] <= segs[min_index][0] && segs[i][2] < segs[min_index][2])
                min_index = i;

            if (segs[i][1] >= segs[max_index][1] && segs[i][2] < segs[max_index][2])
                max_index = i;
        }

        if (segs[min_index][0] == segs[max_index][0]) {
            cout << segs[max_index][2];
        } else {
            cout << segs[min_index][2] + segs[max_index][2];
        }
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
