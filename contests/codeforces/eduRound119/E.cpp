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

template <typename T_List>
void printList(const T_List &List, const bool space = true,
               const bool new_line = true) {
    for (int i = 0; i < List.size(); i++) {
        cout << List[i];

        if (space) cout << ' ';
    }
    if (new_line)
        cout << '\n';
    else
        cout << ' ';
}

const int mXN = int(5e5) + 5;

int main() {
#ifdef TEXT_IO
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;
    vector<vector<int>> locations(mXN);
    int n = 0;

    for (int q = 0; q < Q; q++) {
        int type, x, y;
        cin >> type >> x;

        if (type == 1) {
            locations[x].push_back(n++);
        } else {
            cin >> y;

            if (x == y) continue;

            vector<int> &x_loc = locations[x];
            vector<int> &y_loc = locations[y];

            if (y_loc.size() > x_loc.size()) y_loc.swap(x_loc);

            y_loc.insert(y_loc.end(), x_loc.begin(), x_loc.end());
            x_loc.clear();
        }
    }

    vector<int> A(n, -1);

    for (int x = 0; x < mXN; x++) {
        for (int loc : locations[x]) A[loc] = x;
    }

    printList(A);
}