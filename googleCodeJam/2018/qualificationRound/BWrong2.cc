#include <algorithm>
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



//needs to account for more than 3 parties at once
template<typename T_Pairs>
void printPairs(T_Pairs pairs, const bool pairSpacing = true, const bool accountForWhiteSpace = false, const bool newPairSpace = true, const bool newLine = true) {
    for (int i = 0; i < pairs.size(); i++) {
        cout << pairs[i].first;

        if (pairSpacing)
            cout << ' ';

        cout << pairs[i].second;

        if (!(pairs[i].second == ' ' && accountForWhiteSpace))
            cout << (newPairSpace ? ' ' : '\n');
    }

    if (newLine)
        cout << '\n';
}   

const int NVL = int(1e9) + 5;

void runCase(int tc) {
    int N;
    cin >> N;
    vector<int> p(N);

    for (auto &i : p)
        cin >> i;

    vector<pair<char, char>> ans;

    if (N == 2) {
        if (p[0] != p[1]) {
            pair<int, char> remove(abs(p[0] - p[1]), p[0] > p[1] ? 'A' : 'B');
            ans.push_back(pair<char, char> (remove.second, remove.first == 2 ? remove.second : ' '));
        }

        for (int i = 0; i < min(p[0], p[1]); i++)
            ans.push_back(pair<char, char> ('A', 'B'));
    
    } else {
        
        pair<int, int> currentMax(-NVL, -1);
        for (int i = 0; i < N; i++) {
            if (p[i] > currentMax.first) {
                currentMax.first = p[i];
                currentMax.second = i;
            }
        }

        char pos_char = currentMax.second == 0 ? 'A' : currentMax.second == 1 ? 'B' : 'C';
        int nextHighest = currentMax.second == 0 ? max(p[1], p[2]) : currentMax.second == 1 ? max(p[0], p[2]) : max(p[0], p[1]);

        if (currentMax.first - nextHighest != 0)
            ans.push_back(pair<char, char> (pos_char, currentMax.first - nextHighest == 2 ? pos_char : ' '));
        
        int index_min = 0;
        for (int i = 0; i < N; i++) {
            if (p[index_min] > p[i])
                index_min = i;
        }

        pos_char = index_min == 0 ? 'A' : index_min == 1 ? 'B' : 'C';
        int current_min = p[index_min];
        for (int i = 0; i < current_min; i += 2) {
            testArgs(i, p[index_min]);
            ans.push_back(pair<char, char> (pos_char, p[index_min] - 2 < 0 ? ' ' : pos_char));
            p[index_min] -= 2;
        }

        pair<char, char> reduce(index_min == 0 ? 'B' : 'A', index_min < 2 ? 'C' : 'B');
        int finalVal = index_min == 0 ? min(p[1], p[2]) : index_min == 1 ? min(p[0], p[2]) : min(p[0], p[1]); 
        for (int i = 0; i < finalVal; i++)
            ans.push_back(reduce);
    }


    cout << "Case #" << tc << ": ";
    printPairs(ans, false, true);
}

int main() {
    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cerr << flush;
    }
}