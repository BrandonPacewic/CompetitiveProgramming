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
#include <string>
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

void runCase() {
    auto order = [](string s) -> string {
        set<char> used;
        string str = "";

        for (auto ch : s)
            if (!used.count(ch)) {
                used.insert(ch);
                str += ch;
            }

        return str;
    };

    auto findChars = [](string S) -> array<int, 2> {
        array<int, 2> current = {-1, -1};

        for (int i = 0; i < S.length(); i++) {
            if (S[i] == 'b' && current[0] == -1) current[0] = i;

            if (S[i] == 'c') current[1] = max(current[1], i);
        }

        return current;
    };

    string S, T;
    cin >> S >> T;

    sort(S.begin(), S.end());

    if (S.length() >= 3)
        while (order(S).substr(0, 3) == T) {
            auto current = findChars(S);

            testList(current);
            assert(current[0] != -1 && current[1] != -1);

            S[current[0]] = 'c';
            S[current[1]] = 'b';
        }

    cout << S << '\n';
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