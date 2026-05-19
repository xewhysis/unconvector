#include "BigFraction.h"
#include <QDebug>

BigFraction::BigFraction() {
    numerator = BigInteger(0);
    denominator = BigInteger(1);
}

BigFraction::BigFraction(const BigInteger& n, const BigInteger& d) {
    numerator = n;
    denominator = d;

    normalize();
}

void BigFraction::normalize() {
    BigInteger g = BigInteger::gcd(numerator, denominator);

    numerator = numerator / g;
    denominator = denominator / g;
}

void BigFraction::output() {
    numerator.print();
    qDebug() << "/";
    denominator.print();
}

BigInteger lcm(const BigInteger& a, const BigInteger& b) {
    return a / BigInteger::gcd(a, b) * b;
}

BigFraction BigFraction::operator+(const BigFraction& other) const {
    BigInteger newDenominator = lcm(denominator, other.denominator);
    BigInteger newNumerator = numerator * (newDenominator / denominator)
                              + other.numerator * (newDenominator / other.denominator);
    return BigFraction(newNumerator, newDenominator);
}

BigFraction BigFraction::operator-(const BigFraction& other) const {
    BigInteger newDenominator = lcm(denominator, other.denominator);
    BigInteger newNumerator = numerator * (newDenominator / denominator)
                              - other.numerator * (newDenominator / other.denominator);

    return BigFraction(newNumerator, newDenominator);
}

BigFraction BigFraction::operator*(const BigFraction& other) const {
    BigInteger newNum = numerator * other.numerator;
    BigInteger newDen = denominator * other.denominator;
    return BigFraction(newNum, newDen);
}

BigFraction BigFraction::operator/(const BigFraction& other) const {
    BigInteger newNum = numerator * other.denominator;
    BigInteger newDen = denominator * other.numerator;
    return BigFraction(newNum, newDen);
}

BigInteger BigFraction::floor() const {
    return numerator / denominator;
}

BigInteger BigFraction::remainder() const {
    BigInteger intPart = floor();
    return numerator - intPart * denominator;
}