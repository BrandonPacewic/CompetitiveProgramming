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

void runCase() {
    int N;
    cin >> N;
    vector<int> A(N);

    for (auto &a : A) cin >> a;

    vector<int> B = A;
    sort(B.begin(), B.end());

    string S;
    cin >> S;

    vector<int> ans(N);

    if (S[0] == '1') {
        ans[0] = B[A[0]];
        B.erase(B.begin() + A[0]);
    }

    reverse(B.begin(), B.end());

    for (int i = 1; i < N; i++) {
        if (S[i] == '1') {
            ans[i] = B.back();
            B.pop_back();
        }
    }

    for (int i = 0; i < N; i++) {
        if (S[i] == '0') {
            ans[i] = B.back();
            B.pop_back();
        }
    }

    printList(ans);
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