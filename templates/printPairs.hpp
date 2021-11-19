template<typename T_Pairs>
void printPairs(T_Pairs pairs) {
    for (int i = 0; i < pairs.size(); i++) 
        cout << "pair# " << i << pairs[i].first << ' ' << pairs[i].second << '\n';  
}