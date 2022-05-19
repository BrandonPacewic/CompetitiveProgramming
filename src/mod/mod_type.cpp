/* MIT License
 *
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <cstdint>
#include <istream>
#include <ostream>

template <typename _Tp>
struct mod_type {
    _Tp value;

    mod_type() : value{0} {}
    mod_type(_Tp _value) : value{_value} {}
    ~mod_type() = default;

    explicit operator int() const { return value; }
    explicit operator int64_t() const { return value; }
    explicit operator double() const { return value; }
    explicit operator long double() const { return value; }

    mod_type& operator%=(const mod_type& other) {
        value %= other.value;
        if (value < 0) {
            value += other.value;
        }
        return *this;
    }

    mod_type operator%(const mod_type& other) const {
        mod_type tmp = *this;
        tmp.value %= other.value;
        if (tmp.value < 0) {
            tmp.value += other.value;
        }
        return tmp.value;
    }

    mod_type& operator++() {
        ++value;
        return *this;
    }
    mod_type& operator--() {
        --value;
        return *this;
    }

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

    mod_type operator+(const mod_type& other) const {
        return value + other.value;
    }

    mod_type operator-(const mod_type& other) const {
        return value - other.value;
    }

    mod_type operator*(const mod_type& other) const {
        return value * other.value;
    }

    mod_type operator/(const mod_type& other) const {
        return value / other.value;
    }

    friend std::ostream& operator<<(std::ostream& os, const mod_type& a) {
        return os << a.value;
    }

    friend std::istream& operator>>(std::istream& is, mod_type& a) {
        return is >> a.value;
    }
};
