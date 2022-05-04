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

#ifdef DBG_MODE
template <typename T_Vector>
void testListInList(T_Vector List) {
    cerr << '#' << DBG_COUNT << " __LIST_ARGS__:(";
    DBG_COUNT++;
    for (int i = 0; i < List.size(); i++) {
        cerr << '(';
        for (int k = 0; k < List[i].size(); k++)
            cerr << List[i][k] << (k < List[i].size() - 1 ? ", " : ")");
        cerr << (i < List.size() - 1 ? ", " : ")\n");
    }
}
#else
template <typename T_Vector>
void testListInList(T_Vector List) {
    return;
}
#endif

void runCase() {
    int64_t W, H;
    cin >> W >> H;

    int64_t highArea = 0;

    for (int i = 0; i < 2; i++) {
        int k;
        cin >> k;

        vector<int64_t> X(k);

        for (auto &x : X) cin >> x;

        highArea = max(highArea, (X.back() - X.front()) * H);
    }

    for (int i = 0; i < 2; i++) {
        int k;
        cin >> k;

        vector<int64_t> X(k);

        for (auto &x : X) cin >> x;

        highArea = max(highArea, (X.back() - X.front()) * W);
    }

    cout << highArea << '\n';
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