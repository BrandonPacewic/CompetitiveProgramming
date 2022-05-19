#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

// dbg
#ifdef DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() {
    cerr << endl;
    DBG_COUNT++;
}
template <typename Front, typename... Back>
void DBG_OUT(Front K, Back... T) {
    cerr << ' ' << K;
    DBG_OUT(T...);
}
template <typename T_List>
void testList(T_List List) {
    cerr << '#' << DBG_COUNT << " __LIST_ARGS__: (";
    DBG_COUNT++;
    for (int i = 0; i < List.size(); i++) {
        cerr << List[i] << (i < List.size() - 1 ? ", " : ")\n");
    }
}
#define testArgs(...)                                                     \
    cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", \
        DBG_OUT(__VA_ARGS__)
#else
template <typename T_List>
void testList(T_List List) {
    return;
}
#define testArgs(...)
#endif

void runCase() {
    int N;
    cin >> N;
    vector<int> A(N);

    for (auto &a : A) cin >> a;

    sort(A.begin(), A.end());
    vector<bool> used(N, false);
    bool good = false;
    int operations = 0;

    for (int i = 2; i < N + 1; i++) {
        for (int k = 0; k < N; k++) {
            if (!used[k]) {
                if (A[k] == i) {
                    good = true;
                    used[k] = true;
                } else if (A[k] >= (i + 1) && A[k] % (i + 1) == i) {
                    good = true;
                    operations++;
                    used[k] = true;
                }
            }
        }

        if (!good) {
            cout << -1 << '\n';
            return;
        } else {
            good = false;
        }
    }

    cout << operations << '\n';
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