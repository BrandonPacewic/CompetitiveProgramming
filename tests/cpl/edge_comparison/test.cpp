// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <cassert>

#include "tree.h"

struct Edge {
    int weight;
};

int main() {
    using namespace std;
    using namespace cpl;

    EdgeLess    less;
    EdgeGreater greater;

    ::Edge a{1};
    ::Edge b{2};

    assert(less(a, b));
    assert(greater(b, a));

    assert(less(a, a) == false);
    assert(greater(a, a) == false);

    assert(less(b, a) == false);
    assert(greater(a, b) == false);

    assert(less(b, b) == false);
    assert(greater(b, b) == false);

    assert(less(a, 2));
    assert(greater(2, a));

    assert(less(a, 1) == false);
    assert(greater(1, a) == false);

    assert(less(b, 1) == false);
    assert(greater(1, b) == false);

    assert(less(b, 2) == false);
    assert(greater(2, b) == false);

    assert(less(1, 2));
    assert(greater(2, 1));

    return 0;
}
