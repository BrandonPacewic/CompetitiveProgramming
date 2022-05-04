#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
using namespace std;

// dbg
#ifdef DBG_MODE
int64_t DBG_COUNT = 0;
void DBG_OUT() {
    cerr << endl;
    DBG_COUNT++;
}
template <typename Front, typename... Back>
void DBG_OUT(Front K, Back... T) {
    cerr << ' ' << K;
    DBG_OUT(T...);
}
template <typename T_List>
void testList(T_List List) {
    cerr << '#' << DBG_COUNT << " __LIST_ARGS__: (";
    DBG_COUNT++;
    for (int i = 0; i < List.size(); i++) {
        cerr << List[i] << (i < List.size() - 1 ? ", " : ")\n");
    }
}
#define testArgs(...)                                                     \
    cerr << '#' << DBG_COUNT << " __VA_ARGS__ (" << #__VA_ARGS__ << "):", \
        DBG_OUT(__VA_ARGS__)
#else
template <typename T_List>
void testList(T_List List) {
    return;
}
#define testArgs(...)
#endif

const int MAX = 500;

template <typename T>
void print_reverse(T iterable) {
    for (int i = iterable.size() - 1; i >= 0; i--) {
        std::cout << iterable[i];
    }

    std::cout << '\n';
}

std::vector<int> long_factorials(int n) {
    std::vector<int> res;
    res.push_back(1);

    auto multiply = [&](int itr) -> void {
        int carry = 0;

        for (int i = 0; i < res.size(); i++) {
            int product = res[i] * itr + carry;
            res[i] = product % 10;
            carry = product / 10;
        }

        while (carry) {
            res.push_back(carry % 10);
            carry /= 10;
        }
    };

    for (int itr = 2; itr < n + 1; itr++) {
        multiply(itr);
    }

    assert(res.size() <= MAX);

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    long_factorials(N);
}
