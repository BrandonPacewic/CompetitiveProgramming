#include "../../src/container/encoding.cc"

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

constexpr uint16_t total_tests = 5;

using encoding_output = std::vector<std::pair<char, uint16_t>>;

std::array<std::pair<std::string, encoding_output>, total_tests> test_cases;

void init_test_cases() {
    test_cases[0].first = "";
    test_cases[0].second = {};

    test_cases[1].first = "a";
    test_cases[1].second = {{'a', 1}};

    test_cases[2].first = "aa";
    test_cases[2].second = {{'a', 2}};

    test_cases[3].first = "aba";
    test_cases[3].second = {{'a', 1}, {'b', 1}, {'a', 1}};

    test_cases[4].first = "ababa";
    test_cases[4].second = {{'a', 1}, {'b', 1}, {'a', 1}, {'b', 1}, {'a', 1}};
}

int main() {
    init_test_cases();
    bool all_passed = true;

    std::cout << "Running run_length_encoding tests..." << std::endl;

    std::for_each(
        test_cases.begin(), test_cases.end(), [&](const auto& test_case) {
            bool current_test_passed =
                run_length_encoding<char>(test_case.first) == test_case.second;

            if (!current_test_passed) {
                all_passed = false;
                std::cout << "Failed test case: " << test_case.first
                          << std::endl;
            } else {
                std::cout << "Passed test case: " << test_case.first
                          << std::endl;
            }
        });

    std::cout << "Finished run_length_encoding tests." << std::endl;

    return !all_passed;
}