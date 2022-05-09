// Given n, take the sum of the digits of n. If that value has more than one
// digit, continue reducing in this way until a single-digit number is produced.
// The input will be a non-negative integer.

int digital_root(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum > 9 ? digital_root(sum) : sum;
}