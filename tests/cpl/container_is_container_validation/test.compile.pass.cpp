// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <container.h>

#include <array>
#include <cassert>
#include <vector>

using namespace std;
using namespace cpl;

static_assert(is_container<array<int, 5>>);
static_assert(is_container<vector<int>>);

struct A {};

static_assert(!is_container<A>);

struct B : public A {};

static_assert(!is_container<B>);

struct C : public vector<int> {};
struct D : public C {};
struct E : public array<int, 5> {};

static_assert(is_container<C>);
static_assert(is_container<D>);
static_assert(is_container<E>);

int main() { // compile only
    return 0;
}
