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


int find(const int target, vector<int> list) {
    for (int i = 0; i < list.size(); i++)
        if (list[i] == target)
            return i;
    
    return -1;
}

void runCase(int tc) {
    int n;
    cin >> n;

    vector<int> list(n, 0);

    for (auto &i: list)
        cin >> i;

    int count = 0;
    for (int i = 1; i <= n; i++) {
        int index = find(i, list);
        testArgs(index);
        if (i != index - 1) {
            reverse(list.begin() + i - 1, list.end());
            count++;
            testListInt(list);
        } else 
            count++;

    }

    cout << "Case #" << tc << ": " << count <<  '\n';
}

int main() {
    int tc;
    cin >> tc;

    for (int i = 1; i <= tc; i++) {
        runCase(i);
        cout << flush;
    }
}