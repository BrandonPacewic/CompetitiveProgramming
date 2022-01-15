//modulo http://www.cplusplus.com/forum/general/19502/
template<typename T, typename OP> struct modulo { T bace; }; enum { mod };
template<typename T> modulo<T, decltype(mod)> operator<(const T& front, decltype(mod)) { return  { front }; }
template<typename T_type> T_type operator>(modulo<T_type, decltype(mod)> tail, T_type exponent) { T_type& bace = tail.bace; return bace % exponent < 0 ? (bace % exponent) + exponent : bace % exponent; }

template<typename T, typename T_type>
T mod_const(T_type _a, T_type _b) {
	return T(_a <mod> _b);
}