#include "../../src/container/to_set.cc"

#include <array>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>

constexpr uint16_t total_tests = 5;

std::array<std::pair<std::string, std::set<char>>, total_tests>
generate_to_set_tests() {
    std::array<std::pair<std::string, std::set<char>>, total_tests> tests;

    tests[0] = {
        "abcdefghi",
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'}
    };

    tests[1] = {
        "aabcdefgh",
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}
    };

    tests[2] = {
        "arandomword",
        {'a', 'r', 'a', 'n', 'd', 'o', 'm', 'w', 'o', 'r', 'd'}
    };

    tests[3] = {
        "",
        {}
    };

    tests[4] = {
        "a",
        {'a'}
    };

    return tests;
}

std::array<std::pair<std::string, std::unordered_set<char>>, total_tests>
generate_to_unordered_set_tests() {
    std::array<
        std::pair<std::string, std::unordered_set<char>>,
        total_tests> tests;

    tests[0] = {
        "abcdefghi",
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'}
    };

    tests[1] = {
        "aabcdefgh",
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}
    };

    tests[2] = {
        "arandomword",
        {'a', 'r', 'a', 'n', 'd', 'o', 'm', 'w', 'o', 'r', 'd'}
    };

    tests[3] = {
        "",
        {}
    };

    tests[4] = {
        "a",
        {'a'}
    };

    return tests;
}

bool run_to_set_tests() {
    auto tests = generate_to_set_tests();
    bool passing = true;

    for (uint16_t i = 0; i < total_tests; ++i) {
        const auto& test = tests[i];
        const auto& input = test.first;
        const auto& expected = test.second;
        const auto output = to_set(input);
        
        if (output != expected) {
            std::cerr << "Test " << i + 1 << " failed.\n";
            passing = false;
        }
    }

    return passing;
}

bool run_to_unordered_set_tests() {
    auto tests = generate_to_unordered_set_tests();
    bool passing = true;

    for (uint16_t i = 0; i < total_tests; ++i) {
        const auto& test = tests[i];
        const auto& input = test.first;
        const auto& expected = test.second;
        const auto output = to_unordered_set(input);
        
        if (output != expected) {
            std::cerr << "Test " << i + 1 << " failed.\n";
            passing = false;
        }
    }

    return passing;
}

int main() {
    const bool to_set_passing = run_to_set_tests();
    const bool to_unordered_set_passing = run_to_unordered_set_tests();

    if (to_set_passing && to_unordered_set_passing) {
        std::cerr << "All tests passed!" << std::endl;
    } else {
        std::cerr << "Some tests failed!" << std::endl;
    }

    return !(to_set_passing && to_unordered_set_passing);
}