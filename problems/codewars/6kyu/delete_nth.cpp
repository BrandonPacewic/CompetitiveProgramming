// add necessary includes
#include <algorithm>
#include <unordered_map>
#include <vector>

std::vector<int> deleteNth(std::vector<int> arr, int n) {
    std::vector<int> result;
    std::unordered_map<int, int> occurences;

    for (const auto& item : arr) {
        ++occurences[item];

        if (occurences[item] <= n) {
            result.push_back(item);
        }
    }

    return result;
}

std::vector<int> delete_nth(std::vector<int> sequence, int max_elements) {
    std::vector<int> result;
    std::unordered_map<int, int> occurences;

    std::copy_if(sequence.begin(), sequence.end(), std::back_inserter(result),
                 [&occurences, max_elements](int item) -> bool {
                     return ++occurences[item] <= max_elements;
                 });

    return result;
}