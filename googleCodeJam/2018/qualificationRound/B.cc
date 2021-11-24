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

//dbg pairs
#ifdef DBG_MODE
template<typename T_Pairs> void testPairs(T_Pairs Pairs) { cerr << '#' << DBG_COUNT << " __PAIR_ARGS__: ("; DBG_COUNT++; for (int i = 0; i < Pairs.size(); i++) { cout << Pairs[i].first << '-' << Pairs[i].second << (i < Pairs.size() - 1 ? ", " : ")\n"); } } 
#else
template<typename T_Pairs> void testPairs(T_Pairs Pairs) { return; }
#endif

const int NVL = int(1e9) + 5;
const string ALPH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//max function
int local_max(vector<int> x, const int size) {
    int y = -NVL;
    for (int i = 0; i < size; i++) 
        if (x[i] > y) 
            y = x[i];
    return(y);
}

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


void runCase(int tc) {
    int N;
    cin >> N;
    vector<int> p(N);

    for (auto &i : p)
        cin >> i;

    vector<pair<char, char>> ans;

    pair<int, int> reduce(0, -NVL);
    for (int i = 1; i < N; i++) {
        if (p[i] > p[reduce.first])
            reduce.first = i;
    }

    testList(p);

    reduce.second = p[reduce.first];
    p[reduce.first] = -NVL;

    // testList(p);
    // testArgs(reduce.first, reduce.second);

    int target = local_max(p, N);
    p[reduce.first] = target;
    // testArgs(target);
    p[reduce.first] = target;
    for (int i = reduce.second; i > target; i -= 2) {
            ans.push_back(pair<char, char> (ALPH[reduce.first], i - 2 >= target ? ALPH[reduce.first] : ' '));
            testArgs(i - 2, target);
    }

    for (int i = 0; i < N - 2; i++) {
        testList(p);

        for (int k = 0; k < N; k++)
            if (p[k] <= reduce.second && p[k] != -NVL) {
                reduce.second = p[k];
                reduce.first = k;
            }

        testArgs(reduce.first, reduce.second);

        for (int k = reduce.second; k > 0; k -= 2) 
            ans.push_back(pair<char, char> (ALPH[reduce.first], k - 2 >= 0 ? ALPH[reduce.first] : ' '));
        
        testPairs(ans);
        p[reduce.first] = -NVL;
        reduce.second = NVL;
    }

    testList(p);
    testArgs(target);   

    reduce.first = reduce.second = -NVL;

    for (int i = 0; i < N; i++) {
        if (p[i] == target)
            reduce.first == -NVL ? reduce.first = i : reduce.second = i;
        
        if (reduce.first != -NVL && reduce.second != -NVL)
            break;
    }

    assert(reduce.first != -NVL && reduce.second != -NVL);

    for (int i = 0; i < target; i++) 
        ans.push_back(pair<char, char> (ALPH[reduce.first], ALPH[reduce.second]));
    

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