// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <container.h>

#include <array>
#include <cassert>
#include <vector>

using namespace std;
using namespace cpl;

// Current is_container fails to validate std::array as a valid container.
// static_assert(is_container<array<int, 5>>::value);

static_assert(is_container<vector<int>>);

struct A {};

static_assert(!is_container<A>);

struct B : A {};

static_assert(!is_container<B>);

int main() {  // compile only
    return 0;
}
