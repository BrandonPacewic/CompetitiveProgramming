#include <bits/stdc++.h>
using namespace std;

//dbg
const bool DBG_MODE = false; 
long long dbg_count = 0ll;
template<typename Ints> void testList(Ints List) { if (!DBG_MODE) return; cerr << '#' << dbg_count << " __LIST_ARGS__: ("; dbg_count += 1ll; for (int i: List) { cout << ' ' << i; } cerr << " )" << endl; }
void DBG_OUT() { cerr << endl; dbg_count += 1ll; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
#if DBG_MODE
#define testArgs(...) cerr << '#' << dbg_count << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", DBG_OUT(__VA_ARGS__)
#else
#define testArgs (...)
#endif


const int NVL = int(1e9) + 5;

void runCase(int tc) {
    int x, y;
    string s;
    cin >> x >> y >> s;
    int end_c = (s[0] == '?' || s[0] == 'C') ? 0 : NVL;
    int end_j = (s[0] == '?' || s[0] == 'J') ? 0 : NVL;

    for (int i = 1; i < s.length(); i++) {
        int nend_c = (s[i] == '?' || s[i] == 'C') ? min(end_j + y, end_c) : NVL;
        int nend_j = (s[i] == '?' || s[i] == 'J') ? min(end_j, end_c + x) : NVL;
        end_c = nend_c;
        end_j = nend_j;
    } 
    
    cout << "Case #" << tc << ": " << min(end_c, end_j) << '\n';
}

int main() {
    int tc;
    cin >> tc;

    for (int case_num = 1; case_num <= tc; case_num++) {
        runCase(case_num);
        cerr << flush;
    }
}