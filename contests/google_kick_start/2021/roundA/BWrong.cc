#include <bits/stdc++.h>
using namespace std;

// dbg
#define DBG_MODE
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

bool checkEdge(vector<vector<int>> M, pair<int, int> L) {
    if (!M[L.first][L.second]) return 0;

    if (L.first - 1 < 0 && M[L.first + 1][L.second]) {
        return 1;
    } else if (L.first + 1 > M.size() && M[L.first - 1][L.second]) {
        return 1;
    } else if (L.second - 1 < 0 && M[L.first][L.second + 1]) {
        return 1;
    } else if (L.second + 1 > M[0].size() && M[L.first][L.second - 1]) {
        return 1;
    }

    if ((L.first - 1 < 0 || L.first + 1 > M.size() || L.second - 1 < 0 ||
         L.second + 1 > M[0].size()) &&
            (M[L.first - 1][L.second] != M[L.first + 1][L.second]) ||
        (M[L.first][L.second - 1] != M[L.first][L.second + 1]))
        return 1;

    return 0;
}

void runCase(int tc) {
    int R, C;
    cin >> R >> C;
    vector<vector<int>> M(R, vector<int>(C));

    for (auto &i : M)
        for (auto &k : i) cin >> k;

    int count = 0;
    // find a end square pivot
    for (int i = 0; i < R; i++) {
        for (int k = 0; k < C; k++) {
            if (checkEdge(M, pair<int, int>(i, k))) {
                vector<int> segment(4, 0);
                testArgs(i, k);

                for (int j = 0; i - j >= 0; j++) {
                    // testargs(j);
                    if (M[i - j][k])
                        segment[0]++;
                    else
                        break;
                }

                for (int j = 0; i + j <= R - 1; j++) {
                    // testargs(j);
                    if (M[i + j][k])
                        segment[2]++;
                    else
                        break;
                }

                for (int j = 0; k - j >= 0; j++) {
                    // testargs(j);
                    if (M[i][k - j])
                        segment[1]++;
                    else
                        break;
                }

                for (int j = 0; k + j <= C - 1; j++) {
                    // testargs(j);
                    if (M[i][k + j])
                        segment[3]++;
                    else
                        break;
                }

                testList(segment);

                for (int t = 0; t < 4; t++)
                    for (int m = 0; m < 4; m++) {
                        if (t == m || (t % 2 == 0 && m % 2 == 0) ||
                            (t % 2 != 0 && m % 2 != 0))
                            continue;

                        if (segment[t] / 2 <= segment[m] && segment[t] > 3 &&
                            segment[m] != 1) {
                            count++;
                            testArgs("thing found", segment[t] / 2, segment[m]);
                        }
                    }

                testArgs(count);
            }
        }
    }

    cout << "Case #" << tc << ": " << count << '\n';
}

int main() {
    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cerr << flush;
    }
}