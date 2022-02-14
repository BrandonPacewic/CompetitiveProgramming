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

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

//dbg
#ifdef DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() { cerr << endl; DBG_COUNT++; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
#define test(...) cerr << '#' << DBG_COUNT << " [" << #__VA_ARGS__ << "]:", DBG_OUT(__VA_ARGS__)
#else
#define test(...)
#endif


bool is_vowel(char a) {
    const string vowels = "aeiouAEIOU";
    return vowels.find(a) != string::npos;
}


void run_case(int tc) {
    string kingdom, ans;
    cin >> kingdom;

    if (kingdom.back() == 'y' || kingdom.back() == 'Y')
        ans = "nobody";
    else if (is_vowel(kingdom.back()))
        ans = "Alice";
    else
        ans = "Bob";

    cout << "Case #" << tc << ": " << kingdom << " is ruled by " << ans << '.' << '\n';
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
