#include <bits/stdc++.h>
using namespace std;

// dbg
#define DBG_MODE
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
#ifdef DBG_MODE
template <typename T_List>
void testList(T_List List) {
    cerr << '#' << DBG_COUNT << " __LIST_ARGS__: (";
    DBG_COUNT++;
    for (int i = 0; i < List.size(); i++) {
        cout << List[i] << (i < List.size() - 1 ? ", " : ")\n");
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
    int R, C;
    cin >> R >> C;
    vector<vector<int>> M(R, vector<int>(C));

    for (auto &i : M)
        for (auto &k : i) cin >> k;

    vector<vector<int>> left(R, vector<int>(C, 0)), right(R, vector<int>(C, 0)),
        up(R, vector<int>(C, 0)), down(R, vector<int>(C, 0));

    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            left[r][c] = M[r][c] ? (c > 0 ? left[r][c - 1] : 0) + 1 : 0;
            up[r][c] = M[r][c] ? (r > 0 ? up[r - 1][c] : 0) + 1 : 0;
        }

    for (int r = R - 1; r >= 0; r--)
        for (int c = C - 1; c >= 0; c--) {
            right[r][c] = M[r][c] ? (c < C - 1 ? right[r][c + 1] : 0) + 1 : 0;
            down[r][c] = M[r][c] ? (r < R - 1 ? down[r + 1][c] : 0) + 1 : 0;
        }

    int total = 0;
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            total += max(min(left[r][c], up[r][c] / 2) - 1, 0);
            total += max(min(up[r][c], right[r][c] / 2) - 1, 0);
            total += max(min(right[r][c], down[r][c] / 2) - 1, 0);
            total += max(min(down[r][c], left[r][c] / 2) - 1, 0);

            total += max(min(up[r][c], left[r][c] / 2) - 1, 0);
            total += max(min(right[r][c], up[r][c] / 2) - 1, 0);
            total += max(min(down[r][c], right[r][c] / 2) - 1, 0);
            total += max(min(left[r][c], down[r][c] / 2) - 1, 0);
        }

    cout << total << '\n';
}

// #define TEXT_IO
int main() {
#ifdef TEXT_IO
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    printf("Don't Forget to Submit Without DBG Enabled\n\n");
#endif

    ios::sync_with_stdio(0);
    cin.tie(0);

    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        cout << "Case #" << tc << ": ";
        runCase();
        cerr << flush;
    }
}