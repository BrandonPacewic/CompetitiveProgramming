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
#include <unordered_map>
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


const int INF = int(1e5) + 5;

void runCase() {
    int N;
    cin >> N;
    vector<int> A(N);

    for (auto &a : A)
        cin >> a;

    sort(A.begin(), A.end());
    int aprox = floor(A.back() / 3);
    int best = INF;

    testList(A);
    testArgs(aprox, A.back());

    for (int ones = 0; ones <= 3; ones++) {
        for (int twos = 0; twos <= 3; twos++) {
            for (int threes = max(aprox - 3, 0); threes <= aprox + 3; threes++) {
                int coins = ones + twos + threes;
                bool works = true;

                if (coins >= best)
                    continue;

                for (int a : A) {
                    bool good = false;

                    for (int x = 0; x <= ones; x++) {
                        for (int y = 0; y <= twos; y++) {
                            int need = a - x - (y * 2);

                            if (need >= 0 && need % 3 == 0 && (need / 3) <= threes) {
                                good = true;
                                break;
                            }
                        }
                    }

                    if (!good) {
                        works = false;
                        break;
                    }
                }

                if (works)
                    best = min(best, coins);
            }
        }
    }

    cout << best << '\n';
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