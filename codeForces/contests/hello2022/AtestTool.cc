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

//dbg
#ifdef DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() { cerr << endl; DBG_COUNT++; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
template<typename T_List> void testList(T_List List) { cerr << '#' << DBG_COUNT << " __LIST_ARGS__: ("; DBG_COUNT++; for (int i = 0; i < List.size(); i++) { cerr << List[i] << (i < List.size() - 1 ? ", " : ")\n"); } }
#define testArgs(...) cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", DBG_OUT(__VA_ARGS__)
#else
template<typename T_List> void testList(T_List List) { return; }
#define testArgs(...)
#endif

template<typename T, class T_func>
void print_empty_matrix(const int &_x, const int &_y, T _a, T _b, T_func condition, const bool space = false) {
    for (int x = 0; x < _x; x++) {
        for (int y = 0; y < _y; y++) {
            std::cout << (condition(x, y) ? _b : _a);

            if (space) std::cout << ' ';
        }

        std::cout << '\n';
    }
}

void runCase() {
    int K, N;
    cin >> K >> N;

    for (int i = 0, r = 1; i < N; i++, r += 2) {
        if (r > K) {
            cout << -1 << '\n';
            return;
        }
    }

    int cell = 0, count = 0;
    print_empty_matrix(K, K, '.', 'R', [&](int x, int y) -> bool {
        if (x == cell && y == cell && count < N) {
            count++;
            cell += 2;
            return true;
        }

        return false;
    });
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        runCase();
        cout << flush;
    }
}
