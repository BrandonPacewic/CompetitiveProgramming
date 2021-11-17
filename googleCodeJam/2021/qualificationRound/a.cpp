#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

//dbg
long long dbg_count = 0ll;
void dbg_out1() { cerr << endl; dbg_count += 1ll; }
template<typename Front, typename... Back> void dbg_out1(Front K, Back... T) { cerr << ' ' << K; dbg_out1(T...); }
#define testArgs(...) cerr << '#' << dbg_count << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", dbg_out1(__VA_ARGS__)

const string data_type[1] = { "St6vectorIiSaIiEE" };
void assertListType() { cerr << '#' << dbg_count << " __LIST_ARGS__: ("; dbg_count += 1ll; }
bool findType(string type) { for (auto i: data_type) { if (i == type) return true; } return false; }
template<typename Arr> void testListInt(Arr List) { assert(findType(typeid(List).name())); assertListType(); for (int i: List) { cout << ' ' << i; } cerr << " )" << endl; }



void runCase(int tc) {
    int n;
    cin >> n;

    vector<int> list(n, 0);

    for (auto &i: list)
        cin >> i;

    int cost = 0;
    for (int i = 0; i < n - 1; i++) {
        int index = int(min_element(list.begin() + i, list.end()) - list.begin());
        reverse(list.begin() + i, list.begin() + index + 1);
        cost += index - i + 1;
    }

    cout << "Case #" << tc << ": " << cost <<  '\n';
}

int main() {
    int tc;
    cin >> tc;

    for (int i = 1; i <= tc; i++) {
        runCase(i);
        cout << flush;
    }
}