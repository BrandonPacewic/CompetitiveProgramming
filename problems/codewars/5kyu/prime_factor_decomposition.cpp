#include <string>
#include <vector>

class PrimeDecomp {
   public:
    static std::string factors(int lst);
};

// recursive prime factorization function
// Example output:
//  "(p1**n1)(p2**n2)...(pk**nk)"
// "(2**2)(3**3)(5)(7)(11**2)(17)"
std::string PrimeDecomp::factors(int lst) {
    std::vector<int> primes;
    std::vector<int> powers;

    for (int i = 2; i <= lst; ++i) {
        if (lst % i == 0) {
            primes.push_back(i);
            powers.push_back(0);

            while (lst % i == 0) {
                ++powers[powers.size() - 1];
                lst /= i;
            }
        }
    }

    std::string result;

    for (int i = 0; i < primes.size(); ++i) {
        result += "(";

        if (powers[i] != 1) {
            result +=
                std::to_string(primes[i]) + "**" + std::to_string(powers[i]);
        } else {
            result += std::to_string(primes[i]);
        }

        result += ")";
    }

    return result;
}
