//dbg pairs
#ifdef DBG_MODE
template<typename T_Pairs> void testPairs(T_Pairs Pairs) { cerr << '#' << DBG_COUNT << " __PAIR_ARGS__: ("; DBG_COUNT++; for (int i = 0; i < Pairs.size(); i++) { cout << Pairs[i].first << '-' << Pairs[i].second << (i < Pairs.size() - 1 ? ", " : ")\n"); } } 
#else
template<typename T_Pairs> void testPairs(T_Pairs Pairs) { return; }
#endif