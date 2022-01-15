#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
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


// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }


template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }


template<typename T_iterable>
void print_iterable(const T_iterable &_iterable, const bool _space = true, const bool _new_line = true, int _start = -1, int _end = -1) {
if (_start == -1) _start = 0;
if (_end == -1) _end = int(_iterable.size());

    for (int i = _start; i < _end; i++) {
        std::cout << _iterable[i];
        
        if (_space) std::cout << ' ';
    }    
        if (_new_line)
            std::cout << '\n';
        else 
            std::cout << ' ';
}


void run_case() {
    int N;
    cin >> N;
    vector<array<int, 2>> edges(N);
    vector<vector<int>> adj(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        u--, v--;
        adj[u].push_back(u);
        adj[v].push_back(v);
        edges[i] = {u, v};
    }

    int leaf = -1;

    for (int i = 0; i < N - 1; i++) {
        if (adj[i].size() > 2) {
            cout << -1 << '\n';
            return;
        } else if (adj[i].size() == 1) {
            leaf = i;
        }
    }

    map<array<int, 2>, int> edge_color;

    // Dfs for the leaf that we found
    y_combinator([&](auto self, int node, int parent, int color) -> void {
        for (int neigh : adj[node])
            if (neigh != parent) {
                edge_color[{node, neigh}] = edge_color[{node, neigh}] = color;
                self(neigh, node, 5 - color);
            }
    })(leaf, -1, -2);

    vector<int> ans;

    for (auto e : edges)
        ans.push_back(edge_color[e]);

    print_iterable(ans);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        run_case();
        cout << flush;
    }
}
