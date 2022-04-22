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
#define test(...) cerr << '#' << DBG_COUNT << " [" << #__VA_ARGS__ << "]:", DBG_OUT(__VA_ARGS__)
#else
#define test(...)
#endif


// https://codeforces.com/problemset/problem/1637/A
void run_case() {
    int N;
    cin >> N;
    vector<int> A(N);

    for (auto& a : A)
        cin >> a;

    bool ans = false;

    for (int i = 0; i < N - 1; ++i) {
        if (A[i] > A[i+1]) {
            ans = true;
            break;
        }
    }

    cout << (ans ? "YES" : "NO") << '\n';
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
