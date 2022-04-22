#include <bits/stdc++.h>
using namespace std;

//dbg
#define DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() { cerr << endl; DBG_COUNT++; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
#ifdef DBG_MODE
template<typename T_Ints> void testList(T_Ints List) { cerr << '#' << DBG_COUNT << " __LIST_ARGS__: ("; DBG_COUNT++; for (int i = 0; i < List.size(); i++) { cout << List[i] << (i < List.size() - 1 ? ", " : ")\n"); } }
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
    }    
        if (new_line)
            cout << '\n';
        else 
            cout << ' ';
}

void runCase(int tc) {
    int N;
    string P;
    cin >> N >> P;

    vector<char> Ans;
    for (int i = 0; i < P.length(); i++) 
        Ans.push_back(P[i] == 'E' ? 'S' : 'E');

    cout << "Case #" << tc << ": ";
    printList(Ans, false);
}

int main() {
    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cerr << flush;
    }
}