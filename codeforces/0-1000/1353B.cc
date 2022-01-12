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


const int INF = int(1e9) + 5;

void runCase() {
    auto findMax = [&](vector<int> VEC) -> int {
        int highIndex = 0;
        
        for (int i = 1; i < VEC.size(); i++)
            highIndex = VEC[highIndex] > VEC[i] ? highIndex : i;
        
        return highIndex;
    };

    auto findMin = [&](vector<int> VEC) -> int {
        int lowIndex = 0;

        for (int i = 0; i < VEC.size(); i++)
            lowIndex = VEC[lowIndex] < VEC[i] ? lowIndex : i;

        return lowIndex; 
    };

    auto countTotal = [&](vector<int> VEC) -> int {
        int total = 0;
        
        for (auto v : VEC)
            total += v;
        
        return total;
    };

    int N, K;
    cin >> N >> K;
    vector<int> A(N), B(N);

    for (auto &a : A)
        cin >> a;

    for (auto &b : B)
        cin >> b;

    for (int k = 0; k < K; k++) {
        int nmax = findMax(B);
        int omin = findMin(A);
        A[omin] = B[nmax] > A[omin] ? B[nmax] : A[omin];
        B[nmax] = -INF;
    }

    cout << countTotal(A) << '\n';
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