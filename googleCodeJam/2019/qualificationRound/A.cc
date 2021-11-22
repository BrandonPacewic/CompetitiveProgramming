#include <bits/stdc++.h>
using namespace std;

//dbg
#define DBG_MODE
long long DBG_COUNT = 0ll;
void DBG_OUT() { cerr << endl; DBG_COUNT += 1ll; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
#ifdef DBG_MODE
template<typename T_Ints> void testList(T_Ints List) { cerr << '#' << DBG_COUNT << " __LIST_ARGS__: ("; DBG_COUNT += 1ll; for (int i = 0; i < List.size(); i++) { cout << List[i] << (i < List.size() - 1 ? ", " : ")\n"); } }
#define testArgs(...) cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", DBG_OUT(__VA_ARGS__)
#else
template<typename T_Ints> void testList(T_Ints List) { return; }
#define testArgs(...)
#endif


template<typename T_List>
void printList(T_List List, bool space = true, bool new_line = true) {
    for (int i = 0; i < List.size(); i++) {
        cout << List[i];
        
        if (space)
            cout << ' ';
        
        cout << (new_line && i == List.size() - 1 ? '\n' : ' '); 
    }
}

void runCase(int tc) {
    string N;
    cin >> N;

    vector<int> A(N.length()), B(N.length());
    for (int i = 0; i < N.length(); i++) {
        if (N[i] == '4') {
            A[i] = 2;
            B[i] = 2;
        } else {
            A[i] = N[i] - '0';
        }
    }

    cout << "Case #" << tc << ": ";
    printList(A, false, false);
    printList(B, false, true);
}

int main() {
    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cerr << flush;
    }
}