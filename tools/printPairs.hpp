template<typename T_Pairs>
void printPairs(const T_Pairs &pairs, const bool pairSpacing = true, const bool accountForWhiteSpace = false, const bool newPairSpace = true, const bool newLine = true) {
    for (int i = 0; i < pairs.size(); i++) {
        cout << pairs[i].first;

        if (pairSpacing) cout << ' ';

        cout << pairs[i].second;

        if (!(pairs[i].second == ' ' && accountForWhiteSpace)) cout << (newPairSpace ? ' ' : '\n');
    }

    if (newLine) cout << '\n';
}