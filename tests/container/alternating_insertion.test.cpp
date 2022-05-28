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

#include "../../src/container/alternating_insertion.cpp"

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <vector>

constexpr uint8_t total_tests = 5;

using std::array;
using std::pair;
using std::vector;

array<pair<pair<vector<int>, vector<int>>, vector<int>>, total_tests>
    alternating_insertion_test_cases;

void init_test_cases() {
    alternating_insertion_test_cases[0].first.first = {};
    alternating_insertion_test_cases[0].first.second = {};
    alternating_insertion_test_cases[0].second = {};

    alternating_insertion_test_cases[1].first.first = {1};
    alternating_insertion_test_cases[1].first.second = {};
    alternating_insertion_test_cases[1].second = {1};

    alternating_insertion_test_cases[2].first.first = {1, 2};
    alternating_insertion_test_cases[2].first.second = {};
    alternating_insertion_test_cases[2].second = {1, 2};

    alternating_insertion_test_cases[3].first.first = {1, 2};
    alternating_insertion_test_cases[3].first.second = {3};
    alternating_insertion_test_cases[3].second = {1, 3, 2};

    alternating_insertion_test_cases[4].first.first = {1};
    alternating_insertion_test_cases[4].first.second = {2, 3, 4, 5};
    alternating_insertion_test_cases[4].second = {1, 2, 3, 4, 5};
}

int main() {
    init_test_cases();
    bool all_passed = true;

    std::cout << "Running alternating_insertion tests..." << std::endl;

    std::for_each(alternating_insertion_test_cases.begin(),
                  alternating_insertion_test_cases.end(), [&](auto& test_case) {
                      vector<int> result(test_case.second.size());
                      alternating_insertion(test_case.first.first.begin(),
                                            test_case.first.first.end(),
                                            test_case.first.second.begin(),
                                            test_case.first.second.end(),
                                            result.begin());

                      if (result != test_case.second) {
                          all_passed = false;
                          std::cout << "Test case failed." << std::endl;
                      }
                  });

    std::cout << "Finished running alternating_insertion tests." << std::endl;

    return !all_passed;
}