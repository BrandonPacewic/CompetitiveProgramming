#include <bits/stdc++.h>
using namespace std;

//dbg
// #define DBG_MODE
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


const int INF = int(1e9) + 5;

struct event {
    int start;
    int end;
    int index;
};


bool compair(event a, event b) {
    if (a.start < b.start)
        return 1;
    else 
        return 0;
}

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
    cin >> N;

    vector<event> SE(N);

    for (int i = 0; i < N; i++) {
        cin >> SE[i].start;
        cin >> SE[i].end;
        SE[i].index = i;
    }

    sort(SE.begin(), SE.end(), compair);


    int J_end = -INF, C_end = -INF;
    vector<char> ANS(N);
    for (auto i : SE) {
        testArgs(i.start, i.end);

        if (i.start >= J_end) {
            J_end = i.end;
            ANS[i.index] = 'J';
            continue;
        } else if (i.start >= C_end) {
            C_end = i.end;
            ANS[i.index] = 'C';
            continue;
        } else {
            cout << "Case #" << tc << ": IMPOSSIBLE" << '\n';
            return;
        }

    }

    cout << "Case #" << tc << ": ";
    printList(ANS, false);
}

int main() {
    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cerr << flush;
    }
}
