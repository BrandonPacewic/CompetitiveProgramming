#include <bits/stdc++.h>
using namespace std;

vector<int> revSort(vector<int> list) {
    for (int i = 0; i < list.size() - 1; i++) {
        int index = int(min_element(list.begin() + i, list.end()) - list.begin());
        reverse(list.begin() + i, list.begin() + index + 1);
    }
    return list;
}