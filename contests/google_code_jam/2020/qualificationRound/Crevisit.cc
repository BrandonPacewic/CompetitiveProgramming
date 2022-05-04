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

struct event {
    int start = -1, end = -1, index = -1;

    event() {}

    event(int _start, int _end, int _index)
        : start(_start), end(_end), index(_index) {}

    bool operator<(const event &other) const { return start < other.start; }
};

void runCase(int tc) {
    int N;
    cin >> N;
    vector<event> events(N);

    for (int i = 0; i < N; i++) {
        cin >> events[i].start >> events[i].end;
        events[i].index = i;
    }

    sort(events.begin(), events.end());
    int end_c = -1, end_j = -1;
    vector<char> ans(N, 'n');

    for (const event evn : events) {
        if (evn.start >= end_c) {
            ans[evn.index] = 'C';
            end_c = evn.end;
        } else if (evn.start >= end_j) {
            ans[evn.index] = 'J';
            end_j = evn.end;
        } else {
            cout << "Case #" << tc << ": IMPOSSIBLE" << '\n';
            return;
        }
    }

    cout << "Case #" << tc << ": ";
    print_iterable(ans, false);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cout << flush;
    }
}