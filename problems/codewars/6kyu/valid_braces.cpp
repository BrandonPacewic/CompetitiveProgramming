// "(){}[]"   =>  True
// "([{}])"   =>  True
// "(}"       =>  False
// "[(])"     =>  False
// "[({})](]" =>  False

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

bool is_closing(char test) {
    const std::string closing = ")}]";
    return closing.find(test) != std::string::npos;
}

bool valid_braces(std::string braces) {
    if (braces.length() % 2 != 0) {
        return false;
    }

    std::unordered_map<char, char> opps;
    opps['{'] = '}';
    opps['('] = ')';
    opps['['] = ']';

    std::vector<char> stack;
    bool ans = true;

    auto opp_of_back = [&]() -> char { return opps[stack.back()]; };

    for (const auto& brace : braces) {
        if (is_closing(brace)) {
            if (brace == opp_of_back()) {
                stack.pop_back();
                continue;
            } else {
                ans = false;
                break;
            }
        }

        stack.push_back(brace);
    }

    return ans && int(stack.size()) == 0;
}

int main() {
    std::string test;
    std::cin >> test;

    std::cout << valid_braces(test) << '\n';

    return 0;
}