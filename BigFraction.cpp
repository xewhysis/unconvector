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