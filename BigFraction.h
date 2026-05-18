#pragma once

#include "BigInteger.h"

class BigFraction {
public:
    BigInteger numerator;
    BigInteger denominator;

    BigFraction();
    BigFraction(const BigInteger& n, const BigInteger& d);

    void normalize();
    void output();
};