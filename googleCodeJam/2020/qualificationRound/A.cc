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


template<typename T> bool findInList(T List, T find) {
    for (T i : List)
        if (i == find)
            return true;
    return false;
}

void runCase(int tc) {

    auto compute = [](vector<vector<int>> matrix) -> int {
        int total = 0;
        for (int i = 0; i < matrix.size(); i++)
            total += matrix[i][i];
        
        return total;
    };

    int N;
    cin >> N;

    vector<vector<int>> matrix(N, vector<int> (N));
    for (int i = 0; i < matrix.size(); i++) {
        for (auto &k : matrix[i])
            cin >> k;
    }

    for (int i = 0; i < N; i++) {

    }

    cout << "Case #" << tc << ": " << '\n';
}

int main() {
    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cerr << flush;
    }
}