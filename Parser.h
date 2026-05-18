#pragma once

#include <QString>
#include "BigFraction.h"

class Parser {
public:
    static BigFraction parse(const QString& input, int base);

private:
    static int digitValue(const QString& token);
};