#pragma once
#include <QString>
#include "BigFraction.h"

class Formatter {
public:
    static QString toBase(const BigFraction& fraction, int base);
};