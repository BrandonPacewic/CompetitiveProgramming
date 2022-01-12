#include <algorithm>
#include <array>
#include <bits/stdint-intn.h>
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


void runCase() {
    int N;
    cin >> N;
    vector<int64_t> A(N);

    for (auto &a : A)
        cin >> a;

    array<int64_t, 2> gcds = {0, 0};

    for (int i = 0; i < N; i++)
        gcds[i % 2] = __gcd(gcds[i % 2], A[i]);

    bool sucess[2] = {1, 1};

    for (int i = 0; i < N; i++) {
        int other = (i + 1) % 2;
        sucess[other] = sucess[other] && A[i] % gcds[other] != 0;
    }

    if (sucess[0])
        cout << gcds[0] << '\n';
    else if (sucess[1])
        cout << gcds[1] << '\n';
    else
        cout << '0' << '\n';
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