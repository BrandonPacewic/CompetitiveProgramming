// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <container.h>

#include <cassert>

int main() {
    using namespace std;
    using namespace cpl;
    {
        vector<int> first_input{};
        vector<int> second_input{};
        vector<int> expected_output{};
        vector<int> output_vector(first_input.size() + second_input.size());
        alternating_insertion(
            first_input.begin(), first_input.end(), second_input.begin(), second_input.end(), output_vector.begin());
        assert(output_vector == expected_output);
    }
    {
        vector<int> first_input{1};
        vector<int> second_input{};
        vector<int> expected_output{1};
        vector<int> output_vector(first_input.size() + second_input.size());
        alternating_insertion(
            first_input.begin(), first_input.end(), second_input.begin(), second_input.end(), output_vector.begin());
        assert(output_vector == expected_output);
    }
    {
        vector<int> first_input{1, 2};
        vector<int> second_input{};
        vector<int> expected_output{1, 2};
        vector<int> output_vector(first_input.size() + second_input.size());
        alternating_insertion(
            first_input.begin(), first_input.end(), second_input.begin(), second_input.end(), output_vector.begin());
        assert(output_vector == expected_output);
    }
    {
        vector<int> first_input{1, 2};
        vector<int> second_input{3};
        vector<int> expected_output{1, 3, 2};
        vector<int> output_vector(first_input.size() + second_input.size());
        alternating_insertion(
            first_input.begin(), first_input.end(), second_input.begin(), second_input.end(), output_vector.begin());
        assert(output_vector == expected_output);
    }
    {
        vector<int> first_input{1};
        vector<int> second_input{2, 3, 4, 5};
        vector<int> expected_output{1, 2, 3, 4, 5};
        vector<int> output_vector(first_input.size() + second_input.size());
        alternating_insertion(
            first_input.begin(), first_input.end(), second_input.begin(), second_input.end(), output_vector.begin());
        assert(output_vector == expected_output);
    }

    return 0;
}
