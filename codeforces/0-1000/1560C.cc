#include <bits/stdc++.h>
using namespace std;

//dbg
#define DBG_MODE
long long DBG_COUNT = 0ll;
void DBG_OUT() { cerr << endl; DBG_COUNT += 1ll; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
#ifdef DBG_MODE
template<typename T_Ints> void testList(T_Ints List) { cerr << '#' << DBG_COUNT << " __LIST_ARGS__: ("; DBG_COUNT += 1ll; for (int i = 0; i < List.size(); i++) { cout << List[i] << (i < List.size() - 1 ? ", " : ")\n"); } }
#define testArgs(...) cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", DBG_OUT(__VA_ARGS__)
#else
template<typename T_Ints> void testList(T_Ints List) { return; }
#define testArgs(...)
#endif


//https://codeforces.com/problemset/problem/1560/C
void runCase() {
    int k;
    cin >> k;

    int a = 1, x = 1, i = 1;

    while (k >= x + a) {
        x += a;
        a += 2;
        i += 1;
    }

    int m = k - x + 1;

    cout << (m <= i ? m : i) << ' ' << (m <= i ? i : i - (m - i)) << '\n';
}

int main() {
    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase();
        cerr << flush;
    }
}