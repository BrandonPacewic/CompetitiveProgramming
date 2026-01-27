// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <cassert>
#include <vector>

#include "xutility.h"

int main() {
    using namespace cpl;
    {
        auto factorial = y_combinator([](auto self, int n) -> int { return n <= 1 ? 1 : n * self(n - 1); });

        assert(factorial(0) == 1);
        assert(factorial(1) == 1);
        assert(factorial(5) == 120);
        assert(factorial(10) == 3628800);
    }
    {
        auto gcd = y_combinator([](auto self, int a, int b) -> int { return b == 0 ? a : self(b, a % b); });

        assert(gcd(20, 30) == 10);
        assert(gcd(48, 18) == 6);
        assert(gcd(0, 5) == 5);
        assert(gcd(17, 13) == 1);
    }
    {
        auto fib = y_combinator([](auto self, int n) -> int { return n <= 1 ? n : self(n - 1) + self(n - 2); });

        assert(fib(0) == 0);
        assert(fib(1) == 1);
        assert(fib(10) == 55);
        assert(fib(15) == 610);
    }
    {
        std::vector<std::vector<int>> adj = {{1, 2}, {3, 4}, {}, {}, {}};
        std::vector<int>              visited;

        auto dfs = y_combinator([&](auto self, int node) -> void {
            visited.push_back(node);
            for (int next : adj[node]) {
                self(next);
            }
        });

        dfs(0);
        assert(visited.size() == 5);
        assert(visited[0] == 0);
        assert(visited[1] == 1);
        assert(visited[2] == 3);
        assert(visited[3] == 4);
        assert(visited[4] == 2);
    }
    {
        int  call_count = 0;
        auto counter    = y_combinator([&](auto self, int n) -> int {
            ++call_count;
            return n <= 0 ? 0 : self(n - 1);
        });

        counter(5);
        assert(call_count == 6);
    }

    return 0;
}
