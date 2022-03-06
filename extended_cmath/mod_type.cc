/*
 *
 *
 *
 */

#include <iostream>
#include <istream>

namespace bp {

template<typename _Tp>
struct mod_type {
    _Tp value;

    mod_type() : value{0} {}
    mod_type(_Tp _value) : value{_value} {}

    explicit operator int() const { return value; }
    explicit operator int64_t() const { return value; }
    explicit operator double() const { return value; }
    explicit operator long double() const { return value; }

    // Main feature of mod_type<> class, modular arithmetic in C++ works different
    // than it otherwise should. In C and C++ the % operator creates a value between
    // -b and b when in most other cases the expected return value should be between 
    // 0 and b. This is a simple fix.

    mod_type& operator%=(const mod_type& other) {
        value %= other.value;
        if (value < 0) { value += other.value; }
        return *this;
    }

    mod_type operator%(const mod_type& other) const { 
        mod_type tmp = *this;
        tmp.value %= other.value;
        if (tmp.value < 0) { tmp.value += other.value; }
        return tmp.value;
    }

    mod_type& operator++() { ++value; return *this; }
    mod_type& operator--() { --value; return *this; }

    mod_type& operator+=(const mod_type& other) {
        value += other.value;
        return *this;
    }

    mod_type& operator-=(const mod_type& other) {
        value -= other.value;
        return *this;
    }

    mod_type& operator*=(const mod_type& other) {
        value *= other.value;
        return *this;
    }

    mod_type& operator/=(const mod_type& other) {
        value /= other.value;
        return *this;
    }

    mod_type operator+(const mod_type& other) const 
    { return value + other.value; }

    mod_type operator-(const mod_type& other) const
    { return value - other.value; }

    mod_type operator*(const mod_type& other) const
    { return value * other.value; }

    mod_type operator/(const mod_type& other) const
    { return value / other.value; }

    friend std::ostream& operator<<(std::ostream& os, const mod_type& a)
    { return os << a.value; }

    friend std::istream& operator>>(std::istream& is, mod_type& a)
    { return is >> a.value; }
};

} // namespace bp