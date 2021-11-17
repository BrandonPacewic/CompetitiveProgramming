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
    //case code here

    cout << "Case #" << tc << ": " << '\n';
}

int main() {
    int tc;
    cin >> tc;

    for (int case_num = 1; case_num <= tc; case_num++) {
        runCase(case_num);
        cerr << flush;
    }
}