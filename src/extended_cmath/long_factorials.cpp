/* MIT License
 *
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <cassert>
#include <iostream>
#include <vector>

const int MAX = 500;

template <typename T>
void print_reverse(T iterable) {
    for (int i = iterable.size() - 1; i >= 0; i--) {
        std::cout << iterable[i];
    }

    std::cout << '\n';
}

std::vector<int> long_factorials(int n) {
    std::vector<int> res;
    res.push_back(1);

    auto multiply = [&](int itr) -> void {
        int carry = 0;

        for (int i = 0; i < res.size(); i++) {
            int product = res[i] * itr + carry;
            res[i] = product % 10;
            carry = product / 10;
        }

        while (carry) {
            res.push_back(carry % 10);
            carry /= 10;
        }
    };

    for (int itr = 2; itr < n + 1; itr++) {
        multiply(itr);
    }

    assert(res.size() <= MAX);

    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    auto res = long_factorials(N);
    print_reverse(res);
}
