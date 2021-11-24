template<typename T_Pairs>
void printPairs(T_Pairs pairs, bool pairSpacing = true, bool newPairSpace = true, bool newLine = true) {
    for (int i = 0; i < pairs.size(); i++) {
        cout << pairs[i].first;

        if (pairSpacing)
            cout << ' ';

        cout << pairs[i].second;

        cout << (newPairSpace ? ' ' : '\n');
    }

    if (newLine)
        cout << '\n';
}   