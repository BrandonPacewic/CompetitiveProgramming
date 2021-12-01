//modulo
template<typename T, typename OP> struct modulo { T bace; }; enum { mod };
template<typename T> modulo<T, decltype(mod)> operator<(const T& front, decltype(mod)) { return  { front }; }
int operator>(modulo<int, decltype(mod)> tail, int exponent) { int& bace = tail.bace; return bace % exponent < 0 ? (bace % exponent) + exponent : bace % exponent; }
#define mod <mod>
