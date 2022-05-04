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
#define test(...)                                             \
    cerr << '#' << DBG_COUNT << " [" << #__VA_ARGS__ << "]:", \
        DBG_OUT(__VA_ARGS__)
#else
#define test(...)
#endif

template <typename T_iterable>
void print_iterable(const T_iterable &_iterable, const bool _space = true,
                    const bool _new_line = true, int _start = -1,
                    int _end = -1) {
    if (_start == -1) _start = 0;
    if (_end == -1) _end = int(_iterable.size());

    for (int i = _start; i < _end; i++) {
        std::cout << _iterable[i];

        if (_space) std::cout << ' ';
    }
    if (_new_line)
        std::cout << '\n';
    else
        std::cout << ' ';
}

void run_case(int tc) {
    int N;
    cin >> N;
    vector<int> A(N);

    for (auto &a : A) cin >> a;

    test(A);
    vector<int> ans;
    map<int, int> seen;

    auto total_over = [&](int upper) -> int {
        int best = 0;

        for (int i = 1; i <= upper; i++) {
            int current = 0;

            for (auto item : seen) {
                if (item.first >= i) {
                    current += item.second;
                    test(item);
                }
            }

            best = max(best, current);
        }

        return best;
    };

    test(A);

    for (int i = 0; i < N; i++) {
        seen[A[i]]++;
        ans.push_back(total_over(i + 1));
    }

    cout << "Case #" << tc << ": ";
    print_iterable(ans);
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
