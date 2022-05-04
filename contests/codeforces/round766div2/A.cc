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

void run_case() {
    int N, M, R, C;
    cin >> N >> M >> R >> C;
    vector<string> grid(N);
    bool black = false;

    for (auto &row : grid) {
        cin >> row;

        if (!black && count(row.begin(), row.end(), 'B')) black = true;
    }

    if (!black) {
        cout << -1 << '\n';
        return;
    }

    if (grid[R][C] == 'B') {
        cout << 0 << '\n';
        return;
    }

    for (int i = 0; i < N; i++)
        if (grid[i][C] == 'B') {
            cout << 1 << '\n';
            return;
        }

    for (int i = 0; i < M; i++)
        if (grid[R][i] == 'B') {
            cout << 1 << '\n';
            return;
        }

    cout << 2 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        run_case();
        cout << flush;
    }
}
