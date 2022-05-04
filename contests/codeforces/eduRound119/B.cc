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

const int64_t INF = int64_t(1e15);

template <typename T>
T local_max(std::vector<T> x, const int size) {
    T y = -INF;
    for (int i = 0; i < size; i++)
        if (x[i] > y) y = x[i];

    return y;
}

template <typename T>
T local_min(std::vector<T> x, const int size) {
    T y = INF;
    for (int i = 0; i < size; i++)
        if (x[i] < y) y = x[i];

    return y;
}

void runCase() {
    int64_t W, H;
    cin >> W >> H;

    int64_t K, j;
    vector<vector<int64_t>> cords(4);

    for (auto &cor : cords) {
        cin >> K;

        for (int i = 0; i < K; i++) {
            cin >> j;
            cor.push_back(j);
        }
    }

    vector<int64_t> maxareas(4);

    for (int i = 0; i < 4; i++) {
        int64_t small = local_min(cords[i], cords[i].size());
        int64_t large = local_max(cords[i], cords[i].size());

        if (i <= 1) {
            maxareas[i] = (large - small) * H;
        } else {
            maxareas[i] = (large - small) * W;
        }
    }

    cout << local_max(maxareas, maxareas.size()) << '\n';
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