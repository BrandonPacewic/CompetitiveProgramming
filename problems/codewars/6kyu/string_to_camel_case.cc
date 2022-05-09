// "the-stealth-warrior" gets converted to "theStealthWarrior"
// "The_Stealth_Warrior" gets converted to "TheStealthWarrior"

#include <string>

std::string to_camel_case(std::string text) {
    std::string ans;
    bool upper = false;

    for (const auto& ch : text) {
        if (ch == '-' || ch == '_') {
            upper = true;
            continue;
        }

        ans += (!upper) ? ch : std::toupper(ch);
        upper = false;
    }

    return ans;
}