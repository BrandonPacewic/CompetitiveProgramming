#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

template <typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A, B>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container,
          typename T = typename std::enable_if<
              !std::is_same<T_container, std::string>::value,
              typename T_container::value_type>::type>
std::ostream& operator<<(std::ostream& os, const T_container& container) {
    os << '{';
    std::string separator;

    for (const T& item : container) {
        os << separator << item, separator = ", ";
    }

    return os << '}';
}

#ifdef DBG_MODE
void dbg_out() { std::cerr << std::endl; }
template <typename Head, typename... Tail>
void dbg_out(Head A, Tail... B) {
    std::cerr << ' ' << A;
    dbg_out(B...);
}
#define test(...) std::cerr << "[" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define test(...)
#endif

template <typename T_container>
std::set<char> to_set(const T_container& container) {
    std::set<char> set_obj(container.begin(), container.end());
    return set_obj;
}

struct Name {
    string name, unchanged_name;

    Name(string& _name) : name(_name), unchanged_name(_name) {
        name.erase(remove(name.begin(), name.end(), ' '), name.end());
    }

    friend ostream& operator<<(ostream& os, const Name& name) {
        return os << name.unchanged_name;
    }
};

void run_case(const uint16_t& tc) {
    uint16_t N;
    cin >> N;

    vector<Name> names(N);

    for (uint16_t i = 0; i < N; ++i) {
        string name;
        getline(cin >> ws, name);
        names[i] = Name(name);
    }

    uint16_t best = 0, index = 0;

    for_each(names.begin(), names.end(), [&](const Name& name, const auto& i) {
        uint16_t unique_letters = uint16_t(to_set(name.name).size());

        if (unique_letters > best ||
            (unique_letters == best && name.name < names[index].name)) {
            best = unique_letters;
            index = i;
        }
    });

    cout << "Case #" << tc << ": " << names[index] << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t test_cases;
    std::cin >> test_cases;

    for (uint16_t tc = 1; tc <= test_cases; tc++) {
        run_case(tc);
#ifdef DBG_MODE
        std::cout << std::flush;
#endif
    }

#ifndef DBG_MODE
    std::cout << std::flush;
#endif

    return 0;
}