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

#ifdef DBG_MODE
template<typename T_Vector> void testListInList(T_Vector List) { cerr << '#' << DBG_COUNT << " __LIST_ARGS__:("; DBG_COUNT++; for (int i = 0; i < List.size(); i++) { cerr << '('; for (int k = 0; k < List[i].size(); k++) cerr << List[i][k] << (k < List[i].size() - 1 ? ", " : ")"); cerr << (i < List.size() - 1 ? ", " : ")\n"); } }
#else
template<typename T_Vector> void testListInList(T_Vector List) { return; }
#endif


const int INF = int(1e3) + 2;

void runCase(int tc) {
    int R, C;
    cin >> R >> C;
    vector<string> grid(R);

    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            char cell;
            cin >> cell;
            grid[r] += cell;
        }

    vector<vector<int>> dis(R, vector<int> (C, 0));

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            int currentDis = INF;

            for (int nr = 0; nr < R; nr++) 
                for (int nc = 0; nc < C; nc++) 
                    if (grid[nr][nc] == '1')
                        currentDis = min(currentDis, abs(r - nr) + abs(c - nc));
            
            dis[r][c] = currentDis;
        }
    }

    //round A google kickstart 2019

    testListInList(dis);

    cout << "Case #" << tc << ": " << '\n';
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

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cout << flush;
    }
}