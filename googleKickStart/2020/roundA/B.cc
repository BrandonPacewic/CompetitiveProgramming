#include <bits/stdc++.h>
using namespace std;

//dbg
#ifdef DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() { cerr << endl; DBG_COUNT++; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
template<typename T_List> void testList(T_List List) { cerr << '#' << DBG_COUNT << " __LIST_ARGS__: ("; DBG_COUNT++; for (int i = 0; i < List.size(); i++) { cerr << List[i] << (i < List.size() - 1 ? ", " : ")\n"); } }
#define testArgs(...) cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", DBG_OUT(__VA_ARGS__)
#else
template<typename T_List> void testList(T_List List) { return; }
#define testArgs(...)
#endif


const int INF = int(1e9) + 5;

//dbg
int maxOfGrid(T_Grid Grid) {
    int max_val = -INF;
    for (int i = 0; i < Grid.size(); i++) {
        testList(Grid[i]);

        for (int j = 0; j < Grid[i].size(); j++)
            max_val = max(max_val, Grid[i][j]);
    
    }
    return max_val;
}

void runCase(int tc) {
    auto total = [&](auto stack, int count) -> int {
        int sum = 0;
        for (int i = 0; i < count; i++)
            sum += stack[i];

        return sum;
    };

    int N, K, P;
    cin >> N >> K >> P;
    vector<vector<int>> stacks(N, vector<int> (K));

    for (auto &i : stacks)
        for (auto &k :i)
            cin >> k;

    vector<vector<int>> sum(N, vector<int> (P));
    for (int n = 0; n < N; n++)
        for (int p = 0; p < P; p++) 
            sum[n][p] = total(stacks[n], p + 1); 
        
    vector<vector<int>> dp(N, vector<int> (K, 0));
    for (int i = 1; i < N; i++)
        for (int j = 0; j <= P; j++)
            for (int x = 0; x < min(K, j); x++)
                dp[i][j] = max(dp[i][j], sum[i][x] + dp[i - 1][j - x]);


    cout << "Case #" << tc << ": " << maxOfGrid(dp) << '\n';
}


int main() {
#ifdef TEXT_IO
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0);
    cin.tie(0);

    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cout << flush;
    }
}