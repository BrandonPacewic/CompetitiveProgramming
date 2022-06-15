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

#include "../../src/container/to_set.cpp"

#include <assert.h>

#include <set>
#include <unordered_set>
#include <vector>

int main() {
    using namespace std;
    {
        vector<int> input = {};
        auto output = to_set(input.begin(), input.end());
        assert(output == set<int>());
    }
    {
        vector<int> input = {1, 2, 3, 4, 5};
        set<int> expected = {1, 2, 3, 4, 5};
        auto output = to_set(input.begin(), input.end());
        assert(output == expected);
    }
    {
        vector<int> input = {};
        unordered_set<int> expected = {};
        auto output = to_unordered_set(input.begin(), input.end());
        assert(output == expected);
    }
    {
        vector<int> input = {1, 2, 3, 4, 5};
        unordered_set<int> expected = {1, 2, 3, 4, 5};
        auto output = to_unordered_set(input.begin(), input.end());
        assert(output == expected);
    }

    return 0;
}