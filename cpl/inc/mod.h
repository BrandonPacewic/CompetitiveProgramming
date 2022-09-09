// mod types library header

// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#pragma once
#ifndef MOD_H_
#define MOD_H_
#include <core.h>

#include <cstdint>
#include <iostream>

CPL_BEGIN

template <typename Tp>
struct mod_type {
    Tp value;

    mod_type() : value{0} {}
    mod_type(Tp _value) : value{_value} {}
    ~mod_type() = default;

    explicit operator int() const {
        return value;
    }
    explicit operator int64_t() const {
        return value;
    }
    explicit operator double() const {
        return value;
    }
    explicit operator long double() const {
        return value;
    }

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

template <typename Tp, const int32_t Ceil>
struct static_mod_type {
    Tp value;

    static_mod_type() : value{0} {}
    static_mod_type(Tp _value) : value{_value} {}
    ~static_mod_type() = default;

    explicit operator int() const {
        return value;
    }
    explicit operator int64_t() const {
        return value;
    }
    explicit operator float() const {
        return value;
    }
    explicit operator double() const {
        return value;
    }
    explicit operator long double() const {
        return value;
    }

    static_mod_type& operator%=(const static_mod_type& other) {
        value %= other.value;
        if (value < 0) {
            value += other.value;
        }
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

    static_mod_type& operator/=(const static_mod_type& other) {
        return value /= other.value;
    }

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

    static_mod_type operator++() {
        return *this += 1;
    }

    static_mod_type operator--() {
        return *this -= 1;
    }

    bool operator==(const static_mod_type& other) const {
        return value == other.value;
    }

    bool operator!=(const static_mod_type& other) const {
        return value != other.value;
    }

    bool operator<(const static_mod_type& other) const {
        return value < other.value;
    }

    bool operator>(const static_mod_type& other) const {
        return value > other.value;
    }

    bool operator<=(const static_mod_type& other) const {
        return value <= other.value;
    }

    bool operator>=(const static_mod_type& other) const {
        return value >= other.value;
    }

    friend std::ostream& operator<<(std::ostream& os, const static_mod_type& a) {
        return os << a.value;
    }

    friend std::istream& operator>>(std::istream& is, static_mod_type& a) {
        return is >> a.value;
    }
};

CPL_END

#endif  // MOD_H_
