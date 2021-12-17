#ifndef TEST_SET
#define TEST_SET
#ifdef DBG_MODE
template<typename T_SET> void testSet(T_SET SET) { cerr << '#' << DBG_COUNT << " __SET_ARGS__: ( "; DBG_COUNT++; for (auto ch : SET) cerr << ch << ' '; cerr << ")\n"; }
#else
template<typename T_SET> void testSet(T_SET SET) { return; }
#endif
#endif