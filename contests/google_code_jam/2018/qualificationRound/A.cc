#include <bits/stdc++.h>
using namespace std;

// dbg
//  #define DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() {
    cerr << endl;
    DBG_COUNT++;
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
    int D;
    string P;
    cin >> D >> P;

    if (count(P.begin(), P.end(), 'S') > D) {
        cout << "Case #" << tc << ": IMPOSSIBLE" << '\n';
        return;
    }

    auto countDamage = [&](string P) -> int {
        int damage = 0, charge = 1;
        for (auto i : P)
            if (i == 'S')
                damage += charge;
            else
                charge *= 2;

        testArgs(damage);
        return damage;
    };

    int swaps = 0;
    while (D < countDamage(P) && DBG_COUNT < 45) {
        for (int i = P.length() - 1; i >= 0; i--)
            if (P[i - 1] == 'C' && P[i] == 'S') {
                swap(P[i - 1], P[i]);
                break;
            }
        swaps++;
        testArgs(P);
    }

    cout << "Case #" << tc << ": " << swaps << '\n';
}

int main() {
    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cerr << flush;
    }
}