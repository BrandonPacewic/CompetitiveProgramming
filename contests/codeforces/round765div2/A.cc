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

void run_case() {
    int N, L;
    cin >> N >> L;
    vector<int> A(N);

    for (auto &a : A) cin >> a;

    auto to_binary = [](int a) -> vector<int> {
        vector<int> binary;

        while (a > 0) {
            int rem = int(a % 2);
            a /= 2;
            binary.push_back(rem);
        }

        reverse(binary.begin(), binary.end());
        return binary;
    };

    vector<vector<int>> binarys;

    for (const auto a : A) binarys.push_back(to_binary(a));

    vector<int> common(N);

    for (auto &binary : binarys) {
        if (binary.size() < binarys[0].size() ||
            binary.size() < binarys[1].size()) {
            reverse(binary.begin(), binary.end());
            binary.push_back(0);
            reverse(binary.begin(), binary.end());
        }

        for (int i = 0; i < binary.size(); i++) common[i] += binary[i];
    }

    int best = *max_element(common.begin(), common.end());

    for (auto i : binarys) testList(i);

    testList(common);
    testArgs(best);
    vector<int> target(binarys.front().size());

    for (int i = 0; i < N; i++)
        if (common[i] == best) target[i]++;

    testList(target);
    int ans = 0;

    for (int i = 0; i < target.size(); i++) ans += pow(target[i], 2);

    cout << ans << '\n';
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
