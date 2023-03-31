// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <container.h>

#include <algorithm>
#include <cassert>
#include <vector>

int main() {
    using namespace std;
    using namespace cpl;
    {
        vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        reverse_sort(v);
        assert(is_sorted(v.begin(), v.end()));
    }
    {
        vector<int> v{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        reverse_sort(v);
        assert(is_sorted(v.begin(), v.end()));
    }
    {
        vector<int> v{1, 10, 2, 9, 3, 8, 4, 7, 5, 6};
        reverse_sort(v);
        assert(is_sorted(v.begin(), v.end()));
    }

    return 0;
}
