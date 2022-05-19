#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
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

template <typename T, typename T_iterable>
vector<pair<T, int>> run_length_encoding(const T_iterable &items) {
    vector<pair<T, int>> encoding;
    T previous;
    int count = 0;

    for (const T &item : items)
        if (item == previous) {
            count++;
        } else {
            if (count > 0) encoding.emplace_back(previous, count);

            previous = item;
            count = 1;
        }

    if (count > 0) encoding.emplace_back(previous, count);

    return encoding;
}

void runCase() {
    int N, K;
    int64_t X;
    string S;
    cin >> N >> K >> X >> S;
    X--;

    vector<pair<char, int>> encoding = run_length_encoding<char>(S);
    vector<int64_t> bases;

    for (auto &pa : encoding)
        if (pa.first == '*') bases.push_back(pa.second * K + 1);

    vector<int64_t> stack;

    while (!bases.empty()) {
        stack.push_back(X % bases.back());
        X /= bases.back();
        bases.pop_back();
    }

    string ans = "";

    for (auto pa : encoding) {
        if (pa.first == '*') {
            ans += string(stack.back(), 'b');
            stack.pop_back();
        } else {
            ans += string(pa.second, pa.first);
        }
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