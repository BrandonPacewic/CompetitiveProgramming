#include <bits/stdc++.h>
using namespace std;

//dbg
const bool DBG_MODE = false; 
long long dbg_count = 0ll;
template<typename Ints> void testList(Ints List) { if (DBG_MODE) { cerr << '#' << dbg_count << " __LIST_ARGS__: ("; dbg_count += 1ll; for (int i: List) { cout << ' ' << i; } cerr << " )" << endl; } }
void DBG_OUT() { cerr << endl; dbg_count += 1ll; }
template<typename Front, typename... Back> void DBG_OUT(Front K, Back... T) { cerr << ' ' << K; DBG_OUT(T...); }
#if DBG_MODE
#define testArgs(...) cerr << '#' << dbg_count << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", DBG_OUT(__VA_ARGS__)
#else
#define testArgs (...)
#endif
