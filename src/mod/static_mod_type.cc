/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * satic_mod_type.cc
 */

// Basic static mod type, prevents the value from ever going above the Ceil,
// (keeps the value between 0 and Ceil without ever touching Ceil) used for
// codeforces problems where they state at the end of the problem, "Because the
// answer can be really really big output the answer mod x". This has also been
// used in different google code jam rounds.

#include <cstdint>
#include <istream>
#include <ostream>

// TODO: Check overflow; default is int
typedef int ceil_num;

template<typename _Tp, const ceil_num Ceil>
struct static_mod_type {
	_Tp value;

	static_mod_type() : value{0} {}
	static_mod_type(_Tp _value) : value{_value} {}
	~static_mod_type() = default;

	explicit operator int() const { return value; }
	explicit operator int64_t() const { return value; }
	explicit operator float() const { return value; }
	explicit operator double() const { return value; }
	explicit operator long double() const { return value; }

	static_mod_type& operator%=(const static_mod_type& other) {
		value %= other.value;
		if (value < 0) { value += other.value; }
		return *this;
	}

	static_mod_type& operator+=(const static_mod_type& other) {
		value += other.value;
		return *this %= Ceil;
	}

	static_mod_type& operator-=(const static_mod_type& other) {
		value -= other.value;
		return *this %= Ceil;
	}

	static_mod_type& operator*=(const static_mod_type& other) {
		value *= other.value;
		return *this %= Ceil;
	}

	static_mod_type& operator/=(const static_mod_type& other) 
	{ return value /= other.value; }

	static_mod_type operator+(const static_mod_type& other) const {
		auto tmp = *this;
		return tmp += other;
	}

	static_mod_type operator-(const static_mod_type& other) const {
		auto tmp = *this;
		return tmp -= other;
	}

	static_mod_type operator*(const static_mod_type& other) const {
		auto tmp = *this;
		return tmp *= other;
	}

	static_mod_type operator/(const static_mod_type& other) const {
		auto tmp = *this;
		return tmp /= other;
	}

	static_mod_type operator%(const static_mod_type& other) const {
		auto tmp = *this;
		return tmp %= other;
	}

	static_mod_type operator++() { return *this += 1; }

	static_mod_type operator--() { return *this -= 1; }

	bool operator==(const static_mod_type& other) const 
	{ return value == other.value; }

	bool operator!=(const static_mod_type& other) const
	{ return value != other.value; }

	bool operator<(const static_mod_type& other) const
	{ return value < other.value; }

	bool operator>(const static_mod_type& other) const
	{ return value > other.value; }

	bool operator<=(const static_mod_type& other) const
	{ return value <= other.value; }

	bool operator>=(const static_mod_type& other) const
	{ return value >= other.value; }

	friend std::ostream& operator<<(std::ostream& os, const static_mod_type& a)
	{ return os << a.value; }

	friend std::istream& operator>>(std::istream& is, static_mod_type& a)
	{ return is >> a.value; }
};
