#pragma once

#include "BigInteger.h"

class BigFraction {
public:
    BigInteger numerator;
    BigInteger denominator;

    BigFraction();
    BigFraction(const BigInteger& n, const BigInteger& d);

    BigFraction operator+(const BigFraction& other) const;
    BigFraction operator-(const BigFraction& other) const;
    BigFraction operator*(const BigFraction& other) const;
    BigFraction operator/(const BigFraction& other) const;

    BigInteger floor() const;
    BigInteger remainder() const;

    void normalize();
    void output();
};