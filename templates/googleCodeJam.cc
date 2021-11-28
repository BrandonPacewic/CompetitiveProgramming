#include <bits/stdc++.h>
using namespace std;

//dbg
#define DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() { cerr << endl; DBG_COUNT++; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
#ifdef DBG_MODE
template<typename T_List> void testList(T_List List) { cerr << '#' << DBG_COUNT << " __LIST_ARGS__: ("; DBG_COUNT++; for (int i = 0; i < List.size(); i++) { cout << List[i] << (i < List.size() - 1 ? ", " : ")\n"); } }
#define testArgs(...) cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", DBG_OUT(__VA_ARGS__)
#else
template<typename T_List> void testList(T_List List) { return; }
#define testArgs(...)
#endif


void runCase() {
    //case code here

}


#define TEXT_IO
int main() {
    #ifdef TEXT_IO
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    printf("Don't Forget to Submit Without DBG Enabled\n\n");
    #endif

    ios::sync_with_stdio(0);
    cin.tie(0);

    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        cout << "Case #" << tc << ": ";
        runCase();
        cerr << flush;
    }
}