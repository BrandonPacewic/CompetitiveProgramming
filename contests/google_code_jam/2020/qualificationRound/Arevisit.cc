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

void runCase(int tc) {
    int N;
    cin >> N;
    vector<vector<int>> grid(N, vector<int>(N));

    for (auto &row : grid)
        for (auto &cell : row) cin >> cell;

    int k = 0;

    for (int i = 0; i < N; i++) {
        k += grid[i][i];
    }

    int r = 0, c = 0;
    vector<set<int>> used_rows(N), used_cols(N);
    vector<bool> changed_rows(N, false), changed_cols(N, false);

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            if (used_rows[i].count(grid[i][k]) && !changed_rows[i]) {
                changed_rows[i] = true;
                r++;
            } else
                used_rows[i].insert(grid[i][k]);

            if (used_cols[k].count(grid[i][k]) && !changed_cols[k]) {
                changed_cols[k] = true;
                c++;
            } else
                used_cols[k].insert(grid[i][k]);
        }
    }

    cout << "Case #" << tc << ": " << k << ' ' << r << ' ' << c << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cout << flush;
    }
}