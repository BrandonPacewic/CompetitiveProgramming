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


bool testPrime(int64_t test) {

    if (test == 0 || test == 1)
        return false;

    for (int64_t i = 2; i <= test / int64_t(2); i++)
        if (i % test == 0)
            return false;

    return true;
}

void runCase(int tc) {
    int64_t N;
    int L;
    cin >> N >> L;

    vector<int64_t> A;
    for (int64_t i = N; i >= 0; i--) {
        if (testPrime(i))
            A.push_back(i);
        if (A.size() == 26)
            break;
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