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


const int INF = int(1e9) + 5;

void runCase() {
    int M, N;
    cin >> M >> N;
    vector<vector<int>> A(M, vector<int>(N));

    for (auto &row : A)
        for (auto &cell : row)
            cin >> cell;

    auto possible = [&](int cutoff) -> bool {
        vector<bool> column(N, false);
        bool hasPair = false;

        for (int i = 0; i < M; i++) {
            int rowCount = 0;

            for (int j = 0; j < N; j++) {
                rowCount += A[i][j] >= cutoff;
                column[j] = column[j] || A[i][j] >= cutoff;
            }

            hasPair = hasPair || rowCount >= 2;
        }

        return hasPair && all_of(column.begin(), column.end(), [](bool X) { return X; });
    };

    int low = 0, high = INF;

    while (low < high) {
        int mid = low + (high - low + 1) / 2;

        if (possible(mid)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }

    cout << low << '\n';
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