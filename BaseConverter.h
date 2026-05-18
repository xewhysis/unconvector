#pragma once
#include <QString>
class BaseConverter {
public:
    static QString convert(const QString& input, int p, int q);
};