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

// Neal Wu -> https://www.youtube.com/watch?v=1MS2BS0c6uY&t=13s
template<typename T_List>
void print_list(const T_List &List, const bool space = true, const bool new_line = true, int start = -1, int end = -1) {
    if (start == -1) start = 0;
    if (end == -1) end = List.size();

    for (int i = start; i < end; i++) {
        std::cout << List[i];
        
        if (space) std::cout << ' ';
    }    

    if (new_line)
        std::cout << '\n';
    else
        std::cout << ' ';
}

void runCase() {
    int N;
    cin >> N;

    vector<int> P(N);

    for (auto &p : P)
        cin >> p;

    string S;
    cin >> S;

    vector<int> indices(N);
    iota(indices.begin(), indices.end(), 0);

    testList(indices);

    sort(indices.begin(), indices.end(), [&](int a, int b){
        testArgs(a, b);

        if (S[a] != S[b]) {
            return S[a] < S[b]; 
        } else {
            return P[a] < P[b];
        }
    });

    testList(indices);

    vector<int> ans(N);
    int value = 1;

    for (int index : indices)
        ans[index] = value++;

    print_list(ans);
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