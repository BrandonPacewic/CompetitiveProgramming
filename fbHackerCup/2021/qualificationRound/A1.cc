#include <bits/stdc++.h>
using namespace std;

//dbg
#define DBG_MODE
long long DBG_COUNT = 0ll;
void DBG_OUT() { cerr << endl; DBG_COUNT += 1ll; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
#ifdef DBG_MODE
template<typename T_Ints> void testList(T_Ints List) { cerr << '#' << DBG_COUNT << " __LIST_ARGS__: ("; DBG_COUNT += 1ll; for (int i = 0; i < List.size(); i++) { cout << List[i] << (i < List.size() - 1 ? ", " : ")\n"); } }
#define testArgs(...) cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", DBG_OUT(__VA_ARGS__)
#else
template<typename T_Ints> void testList(T_Ints List) { return; }
#define testArgs(...)
#endif


const string VOWELS = "AEIOU";

void runCase(int tc) {

    auto slove = [&](char find, int type) -> int {
        for (auto i : VOWELS)
            if (i == find)
                return type ? 1 : 0;
        
        return !type ? 1 : 0;
    };

    auto count = [&](string S) -> int {
        int count = 0, type = 0;
        bool same = true;

        for (auto i : VOWELS)
            if (S[0] == i)
                type = 1;

        for (int i = 0; i < S.length(); i++)
            if (!slove(S[i], type)) {
                same = false;
                break;
            }

        return same ? S.length() : -1;
    };

    string S;
    cin >> S;

    if (count(S) == S.length()) {
        cout << "Case #" << tc << ": " << S.length() << '\n';
        return;
    }

    vector<int> x(S.length(), 0);
    for (int k = 0; k < x.size(); k++){

    char target = S[k];
    int type = 0;
    for (auto i : VOWELS)
        if (i == target) 
            type = 1;
        
        int count = 0;
        for (int i = 0; i < S.length(); i++) 
            if (S[i] != target) 
                count += !slove(S[i], type) ? 1 : 2;

            x[k] = count;
    }

    cout << "Case #" << tc << ": " << *min_element(x.begin(), x.end()) <<  '\n';
}

int main() {
    int test_cases;
    cin >> test_cases;

    for (int tc = 1; tc <= test_cases; tc++) {
        runCase(tc);
        cerr << flush;
    }
}