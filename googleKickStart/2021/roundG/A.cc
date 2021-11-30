#include <bits/stdc++.h>
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


void runCase(int tc) {
    int N, D, M;
    int64_t C;
    string S;
    cin >> N >> D >> C >> M >> S;

    int dogs = count(S.begin(), S.end(), 'D');

    if (D < dogs) {
        cout << "Case #" << tc << ": NO" << '\n';
        return;    
    }

    int found = 0;

    for (int i = 0; i < N; i++) {
        testArgs(found, dogs, C);
        
        if (found == dogs) 
            break;

        if (S[i] == 'D') {
            found++;
            C += M;

        } else if (C > 0) {
            C--;
        } else {
            cout << "Case #" << tc << ": NO" << '\n';
            return;
        }
    }

    cout << "Case #" << tc << ": YES" << '\n';
}


int main() {
#ifdef TEXT_IO
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0);
    cin.tie(0);

    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cout << flush;
    }
}