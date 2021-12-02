#ifdef DBG_MODE
template<typename T_Vector> void testListInList(T_Vector List) { cerr << '#' << DBG_COUNT << " __LIST_ARGS__:("; DBG_COUNT++; for (int i = 0; i < List.size(); i++) { cerr << '('; for (int k = 0; k < List[i].size(); k++) cerr << List[i][k] << (k < List[i].size() - 1 ? ", " : ")"); cerr << (i < List.size() - 1 ? ", " : ")\n"); } }
#else
template<typename T_Vector> void testListInList(T_Vector List) { return; }
#endif