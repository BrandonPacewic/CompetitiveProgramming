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

void run_case() {
    int N, M;
    cin >> N >> M;
    vector<int> distances;

    for (int n = 0; n < N; n++)
        for (int m = 0; m < M; m++) {
            int dis = max(n, N - 1 - n) + max(m, M - 1 - m);
            distances.push_back(dis);
        }

    sort(distances.begin(), distances.end());
    print_iterable(distances);
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
