#include "../../src/container/to_set.cc"

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