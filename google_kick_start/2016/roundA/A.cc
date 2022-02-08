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
#define testArgs(...) cerr << '#' << DBG_COUNT << " [" << #__VA_ARGS__ << "]:", DBG_OUT(__VA_ARGS__)
#else
#define testArgs(...)
#endif


void run_case(int tc) {
    auto to_set = [](string _x) -> set<char> {
        set<char> set_obj(_x.begin(), _x.end());

        testArgs(set_obj);

        return set_obj;
    };

    int N;
    cin >> N;
    vector<string> names(N), same(N);

    for (int i = 0; i < N; i++) {
        getline(cin >> ws, names[i]);
        same[i] = names[i];
        names[i].erase(remove(names[i].begin(), names[i].end(), ' '), names[i].end());
    }

    int best = -1, index = -1;

    for (int i = 0; i < N; i++) {
        int unique = int(to_set(names[i]).size());

        testArgs(best, unique, names[i]);

        if (unique > best || (unique == best && names[i] < names[index])) {
            best = unique;
            index = i;
        }
    }

    cout << "Case #" << tc << ": " << same[index] << '\n';
}
    

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        run_case(tc);
        cout << flush;
    }
}
