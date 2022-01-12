#include <bits/stdc++.h>
using namespace std;

// dbg
#ifdef DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() {
  cerr << endl;
  DBG_COUNT++;
}
template <typename Front, typename... Back> void DBG_OUT(Front K, Back... T) {
  cerr << ' ' << K;
  DBG_OUT(T...);
}
template <typename T_List> void testList(T_List List) {
  cerr << '#' << DBG_COUNT << " __LIST_ARGS__: (";
  DBG_COUNT++;
  for (int i = 0; i < List.size(); i++) {
    cerr << List[i] << (i < List.size() - 1 ? ", " : ")\n");
  }
}
#define testArgs(...)                                                          \
  cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):",        \
      DBG_OUT(__VA_ARGS__)
#else
template <typename T_List> void testList(T_List List) { return; }
#define testArgs(...)
#endif

void runCase() {
  int W, H, N;
  cin >> W >> H >> N;

  if (W % 2 != 0 && H % 2 != 0 && N != 1) {
    cout << "NO\n";
    return;
  }

  int current = 1;
  while (current < N) {
    if (H % 2 == 0) {
      current *= 2;
      H /= 2;
    } else if (W % 2 == 0) {
      current *= 2;
      W /= 2;
    } else {
      cout << "NO\n";
      return;
    }
  }

  cout << "YES\n";
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

  while (test_cases--) {
    runCase();
    cerr << flush;
  }
}