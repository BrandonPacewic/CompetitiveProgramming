#include "../../src/other/encoding.cc"

#include <array>
#include <iostream>
#include <string>
#include <vector>

constexpr uint16_t total_tests = 5;

using encoding_output = std::vector<std::pair<char, int>>;

std::array<std::pair<std::string, encoding_output>, total_tests> 
generate_run_length_encoding_tests() {
    std::array<std::pair<std::string, encoding_output>, total_tests> tests;

    tests[0] = {
        "abcdefghi",
        {
            {'a', 1},
            {'b', 1},
            {'c', 1},
            {'d', 1},
            {'e', 1},
            {'f', 1},
            {'g', 1},
            {'h', 1},
            {'i', 1},
        }
    };

    tests[1] = {
        "aabcdefgh",
        {
            {'a', 2},
            {'b', 1},
            {'c', 1},
            {'d', 1},
            {'e', 1},
            {'f', 1},
            {'g', 1},
            {'h', 1},
        }
    };

    tests[2] = {
        "arandomword",
        {
            {'a', 1},
            {'r', 1},
            {'a', 1},
            {'n', 1},
            {'d', 1},
            {'o', 1},
            {'m', 1},
            {'w', 1},
            {'o', 1},
            {'r', 1},
            {'d', 1},
        }
    };

    tests[3] = {
        "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz",
        {
            {'a', 2},
            {'b', 2},
            {'c', 2},
            {'d', 2},
            {'e', 2},
            {'f', 2},
            {'g', 2},
            {'h', 2},
            {'i', 2},
            {'j', 2},
            {'k', 2},
            {'l', 2},
            {'m', 2},
            {'n', 2},
            {'o', 2},
            {'p', 2},
            {'q', 2},
            {'r', 2},
            {'s', 2},
            {'t', 2},
            {'u', 2},
            {'v', 2},
            {'w', 2},
            {'x', 2},
            {'y', 2},
            {'z', 2},
        }
    };

    tests[4] = {
        "aaabbbcccdddeeefffggghhiiiijjkkllllmmmmnnnnooopppqqq"
        "rrrrsssssttttuuuuvvvvwwwwxxxxyyyyzzzz",
        {
            {'a', 3},
            {'b', 3},
            {'c', 3},
            {'d', 3},
            {'e', 3},
            {'f', 3},
            {'g', 3},
            {'h', 2},
            {'i', 4},
            {'j', 2},
            {'k', 2},
            {'l', 4},
            {'m', 4},
            {'n', 4},
            {'o', 3},
            {'p', 3},
            {'q', 3},
            {'r', 4},
            {'s', 5},
            {'t', 4},
            {'u', 4},
            {'v', 4},
            {'w', 4},
            {'x', 4},
            {'y', 4},
            {'z', 4},
        }
    };

    return tests;
}

bool run_encoding_tests() {
    auto tests = generate_run_length_encoding_tests();
    bool passing = true;

    for (uint16_t i = 0; i < total_tests; ++i) {
        const auto& test = tests[i];
        const auto& input = test.first;
        const auto& expected = test.second;
        const auto output = run_length_encoding<char>(input);

        if (output != expected) {
            std::cerr << "Test " << i + 1 << " failed!" << '\n';
            passing = false;
        }
    }

    return passing;
}

int main() {
    const bool all_tests_passed = run_encoding_tests();

    if (all_tests_passed) {
        std::cerr << "All encoding tests passed!" << std::endl;
    }
    else {
        std::cerr << "Some encoding tests failed!" << std::endl;
    }

    return !all_tests_passed;
}