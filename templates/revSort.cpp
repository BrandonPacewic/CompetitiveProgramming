#include <bits/stdc++.h>
using namespace std;

vector<int> revSort(vector<int> list) {
    for (int i = 1; i <= list.size();) {
        for (int k = i; k < list.size(); k++) 
            if (list[k] == i) {
                reverse(list.begin() + i - 1, list.begin() + k + 1);
                goto start;
            }
        
        start:
            i++;
    }
    return list;
}