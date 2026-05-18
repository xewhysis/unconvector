#pragma once

#include <vector>
#include <string>
#include <stdint.h>

class BigInteger {
public:
    static const int BASE = 1000000000;

    std::vector<int> digits;

    BigInteger();
    BigInteger(uint64_t value);
    BigInteger(const std::string& str);

    std::string toString() const;

    bool isZero() const;

    void trim();

    friend bool operator<(const BigInteger& a, const BigInteger& b);
    friend bool operator==(const BigInteger& a, const BigInteger& b);

    friend BigInteger operator+(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator-(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator*(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator/(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator%(const BigInteger& a, const BigInteger& b);

    static BigInteger gcd(BigInteger a, BigInteger b);

    uint32_t divShort(uint32_t value);
    void mulShort(uint32_t value);
    void print(int count = 0);

    void split(int half, BigInteger& high, BigInteger& low) const;
    static BigInteger karatsubaMultiply(const BigInteger& a, const BigInteger& b);
    static BigInteger naiveMultiply(const BigInteger& a, const BigInteger& b);
    friend BigInteger karatsuba(const BigInteger& a, const BigInteger& b);
};