#include <cassert>
#include <iostream>
#include <vector>

const int MAX = 500;

template<typename T>
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
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int N;
	std::cin >> N;

	auto res = long_factorials(N);
	print_reverse(res);
}
