#pragma once

#include <QString>
#include <QMessageBox>

inline void test(QString string) {
    for (QChar symb: string) {
        if (!symb.isDigit()) {
            throw "некорректная запись base/числа";
        }
    }
}