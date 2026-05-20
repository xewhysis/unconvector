#include "Parser.h"
#include "test.h"
#include <QVector>
#include <QMessageBox>

static BigInteger powBig(int base, int power) {
    BigInteger result(1);
    for (int i = 0; i < power; ++i)
        result.mulShort(base);
    return result;
}


QVector<QString> tokenize(const QString& str) {
    QVector<QString> tokens;
    int i = 0;
    while (i < str.size()) {
        if (str[i] == '[') {
            int j = str.indexOf(']', i);
            if (j == -1) {
                QMessageBox::critical(nullptr, "ERROR", "не закрыта ]");
                throw "";
            }
            QString sstring = str.mid(i, j - i + 1);
            if (sstring.size() == 2 || sstring[1].isLetter() && sstring[2] != "]") {
                QMessageBox::critical(nullptr, "ERROR", "неверная запись числа");
                throw "";
            }
            if (sstring[1].isLetter()) {
                sstring = QString(sstring[1]);
            }

            tokens.push_back(sstring);
            i = j + 1;
        } else {
            tokens.push_back(QString(str[i]));
            ++i;
        }
    }
    return tokens;
}
int tokenToDigit(const QString& token, int base) {
    int d;

    if (token.startsWith('[')) {
        QString ss = token.mid(1, token.size() - 2);
        try {
            test(ss);
        } catch (const char* error) {
            QMessageBox::critical(nullptr, "ERROR", error);
            throw "";
        }

        d = ss.toInt();
    }
    else {
        QChar c = token[0];

        if (c.isDigit())
            d = c.digitValue();
        else if (c.isLetter())
            d = c.toUpper().unicode() - 'A' + 10;
        else {
            QMessageBox::critical(nullptr, "ERROR", "некорректный символ");
            throw "";
        }
    }

    if (d >= base) {
        QMessageBox::critical(nullptr, "ERROR", "число не может "
                                                "быть в такой системе счисления");
        throw "";
    }
    return d;
}

BigFraction Parser::parse(const QString& input, int base) {
    QVector<QString> integerTokens;
    QVector<QString> fracTokens;
    QVector<QString> periodTokens;

    bool afterDot = false;
    bool inPeriod = false;
    bool periodClose = false;
    bool periodOpen = false;

    QVector<QString> allTokens = tokenize(input);

    for (const QString& t : allTokens) {
        if (t == "." || t == ",") {
            if (afterDot) {
                QMessageBox::critical(nullptr, "ERROR7", "некорректная запись числа");
                throw "";
            }
            afterDot = true;
            continue;
        }

        if (t == "(") {
            if (periodOpen) {
                QMessageBox::critical(nullptr, "ERROR8", "некорректная запись числа");
                throw "";
            }
            inPeriod = true;
            periodOpen = true;
            continue;
        }

        if (t == ")") {
            if (periodClose) {
                QMessageBox::critical(nullptr, "ERROR9", "некорректная запись числа");
                throw "";
            }
            inPeriod = false;
            periodClose = true;
            continue;
        }

        if (periodClose) {
            QMessageBox::critical(nullptr, "ERROR11", "некорректная запись числа");
            throw "";
        }

        if (!afterDot)
            integerTokens.push_back(t);
        else if (inPeriod)
            periodTokens.push_back(t);
        else
            fracTokens.push_back(t);
    }

    if (afterDot && integerTokens.size() == 0) {
        QMessageBox::critical(nullptr, "ERROR1", "некорректная запись числа");
        throw "";
    }
    if (!afterDot && periodOpen) {
        QMessageBox::critical(nullptr, "ERROR2", "некорректная запись числа");
        throw "";
    }
    if (afterDot && fracTokens.size() == 0 && periodTokens.size() == 0) {
        QMessageBox::critical(nullptr, "ERROR3", "некорректная запись числа");
        throw "";
    }

    if (periodOpen && periodTokens.size() == 0) {
        QMessageBox::critical(nullptr, "ERROR4", "некорректная запись числа");
        throw "";
    }
    if (periodOpen && !afterDot) {
        QMessageBox::critical(nullptr, "ERROR5", "некорректная запись числа");
        throw "";
    }
    if ((!periodOpen && periodClose) || (periodOpen && !periodClose)) {
        QMessageBox::critical(nullptr, "ERROR6", "некорректная запись числа");
        throw "";
    }

    BigInteger I(0);

    for (const QString& token : integerTokens) {
        int d = tokenToDigit(token, base);

        I.mulShort(base);
        I = I + BigInteger(d);
    }

    BigInteger F(0);

    for (const QString& token : fracTokens) {
        int d = tokenToDigit(token, base);

        F.mulShort(base);
        F = F + BigInteger(d);
    }

    BigInteger P(0);

    for (const QString& token : periodTokens) {
        int d = tokenToDigit(token, base);

        P.mulShort(base);
        P = P + BigInteger(d);
    }

    int k = fracTokens.size();
    int m = periodTokens.size();

    if (m == 0) {
        BigInteger pk = powBig(base, k);

        BigInteger num = I * pk + F;
        BigInteger den = pk;

        return BigFraction(num, den);
    }

    BigInteger pk = powBig(base, k);
    BigInteger pm = powBig(base, m);

    BigInteger num =
        I * pk * (pm - BigInteger(1))
        + F * (pm - BigInteger(1))
        + P;

    BigInteger den =
        pk * (pm - BigInteger(1));

    return BigFraction(num, den);
}