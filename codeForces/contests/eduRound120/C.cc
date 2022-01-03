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


const int64_t INF64 = int64_t(2e18) + 5;

void runCase() {
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    int64_t total = 0;

    for (auto &a : A) {
        cin >> a;
        total += a;
    }

    sort(A.begin(), A.end());

    if (accumulate(A.begin(), A.end(), 0ll) <= K) {
        cout << 0 << '\n';
        return;
    }

    vector<int64_t> prefixsum(N + 1, 0);

    for (int i = 0; i < N; i++)
        prefixsum[i + 1] = prefixsum[i] + A[i];

    int64_t best = INF64;

    for (int i = 0; i < N; i++) {
        int64_t sum = prefixsum[N - i] + A[0] * i;

        int64_t need = max<int64_t>((sum - K + i) / (i + 1), 0);
        best = min(best, need + i);
    }

    cout << best << '\n';
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