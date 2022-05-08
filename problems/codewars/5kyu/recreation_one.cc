// 1, 246, 2, 123, 3, 82, 6, 41 are the divisors of number 246. Squaring these divisors we get: 1, 60516, 4, 15129, 9, 6724, 36, 1681. The sum of these squares is 84100 which is 290 * 290.

// Task
// Find all integers between m and n (m and n integers with 1 <= m <= n) such that the sum of their squared divisors is itself a square.

// We will return an array of subarrays or of tuples (in C an array of Pair) or a string. The subarrays (or tuples or Pairs) will have two elements: first the number the squared divisors of which is a square and then the sum of the squared divisors.

#include <cmath>
#include <utility>
#include <vector>

class SumSquaredDivisors
{
public:
    static std::vector<
        std::pair<long long, long long>
    > listSquared(long long m, long long n);
};

// Example output:
// list_squared(1, 250) --> [[1, 1], [42, 2500], [246, 84100]]
// list_squared(42, 250) --> [[42, 2500], [246, 84100]]
std::vector<
    std::pair<long long, long long>
> SumSquaredDivisors::listSquared(long long m, long long n) {
    std::vector<std::pair<long long, long long>> result;
    for (long long i = m; i <= n; i++) {
        long long sum = 0;
        for (long long j = 1; j <= i; j++) {
            if (i % j == 0) {
                sum += j * j;
            }
        }
        if (sqrt(sum) == floor(sqrt(sum))) {
            result.push_back(std::make_pair(i, sum));
        }
    }
    return result;
}