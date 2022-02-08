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
#include <set>
#include <vector>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

//dbg
#ifdef DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() { cerr << endl; DBG_COUNT++; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
#define testArgs(...) cerr << '#' << DBG_COUNT << " [" << #__VA_ARGS__ << "]:", DBG_OUT(__VA_ARGS__)
#else
#define testArgs(...)
#endif


void run_case(int tc) {
    int R, C;
    cin >> R >> C;
    vector<vector<int>> grid(R, vector<int>(C));
    vector<vector<bool>> checked(R, vector<bool>(C, false));

    for (auto &row : grid)
        for (auto &cell : row)
            cin >> cell;

    auto get_value = [&](pair<int, int> target) -> int {
        return grid[target.first][target.second];
    };

    auto locate_low = [&](pair<int, int> center) -> pair<int, int> {
        array<int, 4> adj = {
            grid[center.first - 1][center.second],
            grid[center.first][center.second + 1],
            grid[center.first + 1][center.second],
            grid[center.first][center.second - 1],
        };

        int best = adj[0], loc = 0;

        for (int i = 1; i < 4; i++) 
            if (adj[i] < best) {
                best = adj[i];
                loc = i;
            }

        switch (loc) {
            case 0:
                return {center.first - 1, center.second};

            case 1:
                return {center.first, center.second + 1};

            case 2:
                return {center.first + 1, center.second};

            default:
                return {center.first, center.second - 1}; 
        }

    };

    auto pathfind = [&](pair<int, int> start) -> int {
        int best = -1;

        while (true) {

        }
    };

    int sum = 0;

    for (int r = 1; r < R - 1; r++) {
        for (int c = 1; c < C - 1; c++) {
            if (!checked[r][c]) {
                sum += pathfind({r, c});
            }
        }
    }

    cout << "Case #" << tc << ": " << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        run_case(tc);
        cout << flush;
    }
}
