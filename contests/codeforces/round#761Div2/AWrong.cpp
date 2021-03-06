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

const string ALPH = "abcdefghijklmonpqrstuvwxyz";

void runCase() {
    auto count = [&](string a, char b) -> int {
        int count = 0;

        for (int i = 0; i < a.length(); i++)
            if (a[i] == b) count++;

        return count;
    };

    string S, T;
    cin >> S >> T;

    string ans = "";

    for (int i = 0; i < count(S, 'a'); i++) {
        ans += 'a';
    }

    char next;

    if (T[1] == 'b' && ans.length() > 0)
        next = 'c';
    else
        next = 'b';

    for (int i = 0; i < count(S, next); i++) {
        ans += next;
    }

    for (int i = 0; i < count(S, next == 'b' ? 'c' : 'b'); i++) {
        ans += next == 'b' ? 'c' : 'b';
    }

    for (int i = 3; i < ALPH.length(); i++) {
        int letterCount = count(S, ALPH[i]);

        while (letterCount--) ans += ALPH[i];
    }

    cout << ans << '\n';
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