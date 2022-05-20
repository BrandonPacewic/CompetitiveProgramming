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

#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>

constexpr uint16_t total_tests = 5;

std::array<std::pair<std::string, std::set<char>>, total_tests> set_test_cases;
std::array<std::pair<std::string, std::unordered_set<char>>, total_tests>
    unordered_set_test_cases;

void init_set_test_cases() {
    set_test_cases[0].first = "";
    set_test_cases[0].second = {};

    set_test_cases[1].first = "a";
    set_test_cases[1].second = {'a'};

    set_test_cases[2].first = "aa";
    set_test_cases[2].second = {'a'};

    set_test_cases[3].first = "aba";
    set_test_cases[3].second = {'a', 'b'};

    set_test_cases[4].first = "ababa";
    set_test_cases[4].second = {'a', 'b'};
}

void init_unordered_set_test_cases() {
    unordered_set_test_cases[0].first = "";
    unordered_set_test_cases[0].second = {};

    unordered_set_test_cases[1].first = "a";
    unordered_set_test_cases[1].second = {'a'};

    unordered_set_test_cases[2].first = "aa";
    unordered_set_test_cases[2].second = {'a'};

    unordered_set_test_cases[3].first = "aba";
    unordered_set_test_cases[3].second = {'a', 'b'};

    unordered_set_test_cases[4].first = "ababa";
    unordered_set_test_cases[4].second = {'a', 'b'};
}

int main() {
    init_set_test_cases();
    init_unordered_set_test_cases();
    bool all_passed = true;

    std::cout << "Running to_set tests..." << std::endl;

    std::for_each(set_test_cases.begin(), set_test_cases.end(),
                  [&](const auto& test_case) {
                      bool current_test_passed =
                          to_set(test_case.first) == test_case.second;

                      if (!current_test_passed) {
                          all_passed = false;
                          std::cout << "Failed test case: " << test_case.first
                                    << std::endl;
                      } else {
                          std::cout << "Passed test case: " << test_case.first
                                    << std::endl;
                      }
                  });

    std::cout << "Finished to_set tests.\n";
    std::cout << "Running to_unordered_set tests..." << std::endl;

    std::for_each(unordered_set_test_cases.begin(),
                  unordered_set_test_cases.end(), [&](const auto& test_case) {
                      bool current_test_passed =
                          to_unordered_set(test_case.first) == test_case.second;

                      if (!current_test_passed) {
                          all_passed = false;
                          std::cout << "Failed test case: " << test_case.first
                                    << std::endl;
                      } else {
                          std::cout << "Passed test case: " << test_case.first
                                    << std::endl;
                      }
                  });

    std::cout << "Finished to_unordered_set tests." << std::endl;

    return !all_passed;
}