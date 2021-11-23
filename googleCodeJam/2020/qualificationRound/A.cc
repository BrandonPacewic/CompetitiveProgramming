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


template<typename T_List, typename Type> bool findInList(T_List List, Type find) {
    for (Type i : List)
        if (i == find)
            return true;
    return false;
}

void runCase(int tc) {

    auto trace = [](vector<vector<int>> matrix) -> int {
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

    int rows = 0;
    for (int i = 0; i < N; i++) {

        vector<int> used;
        for (auto k : matrix[i]) {

            if (findInList(used, k)) {
                rows++;
                break;
            } else {
                used.push_back(k);
            }
        }
    }

    int columns = 0;
    for (int i = 0; i < N; i++) {

        vector<int> used;
        for (int k = 0; k < N; k++) {

            if (findInList(used, matrix[k][i])) {
                columns++;
                break;
            } else {
                used.push_back(matrix[k][i]);
            }
        }
    }

    cout << "Case #" << tc << ": " << trace(matrix) << ' ' << rows << ' ' << columns << '\n';
}

int main() {
    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cerr << flush;
    }
}