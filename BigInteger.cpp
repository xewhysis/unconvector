#include "BigInteger.h"
#include <QDebug>
#include <algorithm>
#include <sstream>
#include <iomanip>
BigInteger::BigInteger() {
    digits.push_back(0);
}
BigInteger::BigInteger(uint64_t value) {
    while (value) {
        digits.push_back(value % BASE);
        value /= BASE;
    }
    if (digits.empty())
        digits.push_back(0);
}
BigInteger::BigInteger(const std::string& str) {
    for (int i = str.size(); i > 0; i -= 9) {
        int start = std::max(0, i - 9);
        int len = i - start;
        digits.push_back(std::stoi(str.substr(start, len)));
    }
    trim();
}
void BigInteger::trim() {
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();
}
bool BigInteger::isZero() const {
    return digits.size() == 1 && digits[0] == 0;
}
std::string BigInteger::toString() const {
    std::stringstream ss;
    ss << digits.back();
    for (int i = digits.size() - 2; i >= 0; --i) {
        ss << std::setw(9) << std::setfill('0') << digits[i];
    }
    return ss.str();
}
bool operator<(const BigInteger& a, const BigInteger& b) {
    if (a.digits.size() != b.digits.size())
        return a.digits.size() < b.digits.size();
    for (int i = a.digits.size() - 1; i >= 0; --i) {
        if (a.digits[i] != b.digits[i])
            return a.digits[i] < b.digits[i];
    }
    return false;
}
bool operator==(const BigInteger& a, const BigInteger& b) {
    return a.digits == b.digits;
}
BigInteger operator+(const BigInteger& a, const BigInteger& b) {
    BigInteger res;
    res.digits.clear();
    int carry = 0;
    for (size_t i = 0; i < std::max(a.digits.size(), b.digits.size()) ||
                       carry; ++i) {
        long long cur = carry;
        if (i < a.digits.size()) cur += a.digits[i];
        if (i < b.digits.size()) cur += b.digits[i];
        res.digits.push_back(cur % BigInteger::BASE);
        carry = cur / BigInteger::BASE;
    }
    return res;
}
BigInteger operator-(const BigInteger& a, const BigInteger& b) {
    BigInteger res = a;
    int carry = 0;
    for (size_t i = 0; i < b.digits.size() || carry; ++i) {
        res.digits[i] -= carry + (i < b.digits.size() ? b.digits[i] : 0);
        carry = 0;
        if (res.digits[i] < 0) {
            res.digits[i] += BigInteger::BASE;
            carry = 1;
        }
    }
    res.trim();
    return res;
}

void BigInteger::mulShort(uint32_t value) {
    long long carry = 0;
    for (size_t i = 0; i < digits.size() || carry; ++i) {
        if (i == digits.size())
            digits.push_back(0);
        long long cur = carry + 1LL * digits[i] * value;
        digits[i] = cur % BASE;
        carry = cur / BASE;
    }
    trim();
}
uint32_t BigInteger::divShort(uint32_t value) {
    long long rem = 0;
    for (int i = digits.size() - 1; i >= 0; --i) {
        long long cur = digits[i] + rem * BASE;
        digits[i] = cur / value;
        rem = cur % value;
    }
    trim();
    return rem;
}
BigInteger operator/(const BigInteger& a, const BigInteger& b) {
    BigInteger cur;
    BigInteger res;
    res.digits.assign(a.digits.size(), 0);
    for (int i = a.digits.size() - 1; i >= 0; --i) {
        cur.digits.insert(cur.digits.begin(), a.digits[i]);
        cur.trim();
        int x = 0;
        int l = 0;
        int r = BigInteger::BASE - 1;
        while (l <= r) {
            int m = (l + r) / 2;
            BigInteger t = b;
            t.mulShort(m);
            if (!(cur < t)) {
                x = m;
                l = m + 1;
            }
            else
                r = m - 1;
        }
        BigInteger t = b;
        t.mulShort(x);
        cur = cur - t;
        res.digits[i] = x;
    }
    res.trim();
    return res;
}
BigInteger operator%(const BigInteger& a, const BigInteger& b) {
    return a - (a / b) * b;
}
BigInteger BigInteger::gcd(BigInteger a, BigInteger b) {
    while (!b.isZero()) {
        BigInteger r = a % b;
        a = b;
        b = r;
    }
    return a;
}


void BigInteger::split(int half, BigInteger& high, BigInteger& low) const {
    low.digits.clear();
    high.digits.clear();

    if (half >= static_cast<int>(digits.size())) {
        low = *this;
        high = BigInteger(0);
        return;
    }

    for (int i = 0; i < half && i < static_cast<int>(digits.size()); ++i) {
        low.digits.push_back(digits[i]);
    }
    low.trim();

    for (int i = half; i < static_cast<int>(digits.size()); ++i) {
        high.digits.push_back(digits[i]);
    }
    high.trim();
}

BigInteger BigInteger::naiveMultiply(const BigInteger& a, const BigInteger& b) {
    int maxSize = a.digits.size() + b.digits.size();
    std::vector<long long> temp(maxSize, 0);

    for (size_t i = 0; i < a.digits.size(); ++i) {
        for (size_t j = 0; j < b.digits.size(); ++j) {
            temp[i + j] += 1LL * a.digits[i] * b.digits[j];
        }
    }

    BigInteger result;
    result.digits.resize(maxSize);
    long long carry = 0;

    for (int i = 0; i < maxSize; ++i) {
        carry += temp[i];
        result.digits[i] = carry % BASE;
        carry /= BASE;
    }

    result.trim();
    return result;
}

BigInteger BigInteger::karatsubaMultiply(const BigInteger& a, const BigInteger& b) {
    if (a.digits.empty() || b.digits.empty()) {
        return BigInteger(0);
    }

    if (a.digits.size() <= 64 || b.digits.size() <= 64) {
        return naiveMultiply(a, b);
    }

    if (std::abs(static_cast<int>(a.digits.size()) - static_cast<int>(b.digits.size())) > 64) {
        return naiveMultiply(a, b);
    }

    int n = std::max(a.digits.size(), b.digits.size());
    int half = n / 2;

    BigInteger aLow, aHigh, bLow, bHigh;
    a.split(half, aHigh, aLow);
    b.split(half, bHigh, bLow);

    BigInteger z0 = karatsubaMultiply(aLow, bLow);
    BigInteger z2 = karatsubaMultiply(aHigh, bHigh);

    BigInteger sumA = aLow + aHigh;
    BigInteger sumB = bLow + bHigh;
    BigInteger z1 = karatsubaMultiply(sumA, sumB);
    z1 = z1 - z2 - z0;

    z2.digits.insert(z2.digits.begin(), half * 2, 0);
    z1.digits.insert(z1.digits.begin(), half, 0);

    return z0 + z1 + z2;
}

BigInteger operator*(const BigInteger& a, const BigInteger& b) {
    return BigInteger::karatsubaMultiply(a, b);
}


void BigInteger::print(int count) {
    if (count == digits.size()) return;
    count++;
    print(count);
    qDebug() << digits[count - 1];
}