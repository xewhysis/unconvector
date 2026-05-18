#include "Formatter.h"
#include <QMessageBox>
#include <map>
static QString digitToString(int d) {
    if (d < 10)
        return QString::number(d);
    if (d < 36)
        return QString(QChar('A' + d - 10));
    return QString("[%1]").arg(d);
}
QString Formatter::toBase(const BigFraction& fraction, int base) {
    BigInteger integerPart = fraction.numerator / fraction.denominator;
    BigInteger remainder = fraction.numerator % fraction.denominator;
    QString intResult;
    if (integerPart.isZero())
        intResult = "0";
    else {
        while (!integerPart.isZero()) {
            BigInteger temp = integerPart;
            int rem = temp.divShort(base);
            intResult = digitToString(rem) + intResult;
            integerPart = temp;
        }
    }
    if (remainder.isZero())
        return intResult;
    QString frac;
    std::map<std::string, int> seen;
    while (!remainder.isZero()) {
        std::string key = remainder.toString();
        if (seen.count(key)) {
            int pos = seen[key];
            frac.insert(pos, '(');
            frac += ')';
            break;
        }
        seen[key] = frac.size();
        remainder.mulShort(base);
        BigInteger digit = remainder / fraction.denominator;
        remainder = remainder % fraction.denominator;
        frac += digitToString(std::stoi(digit.toString()));
        if (frac.size() > 100000) {
            frac += "...";
            QMessageBox::information(nullptr, "INFO", "Полная запись результата слишком длинная. "
                                                      "Показаны первые 100000 символов.");
            break;
        }
    }
    return intResult + "." + frac;
}