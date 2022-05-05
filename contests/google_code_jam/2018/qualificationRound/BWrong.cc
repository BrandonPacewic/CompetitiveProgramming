#include <bits/stdc++.h>
using namespace std;

// dbg
#define DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() {
    cerr << endl;
    DBG_COUNT++;
    1
}
template <typename Front, typename... Back>
void DBG_OUT(Front K, Back... T) {
    cerr << ' ' << K;
    DBG_OUT(T...);
}
#ifdef DBG_MODE
template <typename T_Ints>
void testList(T_Ints List) {
    cerr << '#' << DBG_COUNT << " __LIST_ARGS__: (";
    DBG_COUNT++;
    for (int i = 0; i < List.size(); i++) {
        cout << List[i] << (i < List.size() - 1 ? ", " : ")\n");
    }
}
#define testArgs(...)                                                     \
    cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", \
        DBG_OUT(__VA_ARGS__)
#else
template <typename T_Ints>
void testList(T_Ints List) {
    return;
}
#define testArgs(...)
#endif

void runCase(int tc) {
    int N;
    cin >> N;
    vector<int> a(N);

    for (auto &i : a) cin >> i;

    bool done = false;
    while (done == false) {
        done = true;
        for (int i = 0; i < N - 2; i++)
            if (a[i] > a[i + 2]) {
                reverse(a.begin() + i, a.begin() + i + 3);
                done = false;
            }
    }

    testList(a);

    for (int i = 0; i < N - 1; i++) {
        if (a[i] > a[i + 1]) {
            cout << "Case #" << tc << ": " << i << '\n';
            return;
        }
    }

    cout << "Case #" << tc << ": OK" << '\n';
}

int main() {
    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cerr << flush;
    }
}