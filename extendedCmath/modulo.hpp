//modulo http://www.cplusplus.com/forum/general/19502/
template<typename T, typename OP> struct modulo { T bace; }; enum { mod };
template<typename T> modulo<T, decltype(mod)> operator<(const T& front, decltype(mod)) { return  { front }; }
template<typename T_IntType> T_IntType operator>(modulo<T_IntType, decltype(mod)> tail, T_IntType exponent) { T_IntType& bace = tail.bace; return bace % exponent < 0 ? (bace % exponent) + exponent : bace % exponent; }
