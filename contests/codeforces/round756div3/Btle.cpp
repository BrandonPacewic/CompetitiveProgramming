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

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
    os << '{';
    string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << '}';
}

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
#define testArgs(...)                                         \
    cerr << '#' << DBG_COUNT << " [" << #__VA_ARGS__ << "]:", \
        DBG_OUT(__VA_ARGS__)
#else
#define testArgs(...)
#endif

void run_case() {
    int A, B;
    cin >> A >> B;
    int total = 0;

    while (A > 0 && B > 0) {
        if (A > B) {
            A -= 3;
            B--;
        } else if (B > A) {
            B -= 3;
            A--;
        } else {
            B -= 2;
            A -= 2;
        }

        total++;
    }

    if (A + B < 0) {
        total--;
    }

    cout << total << '\n';
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
