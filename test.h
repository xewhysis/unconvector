#include <QString>
#include <QMessageBox>

void test(QString string) {
    for (QChar symb: string) {
        if (!symb.isDigit()) {
            throw "некорректная запись base";
        }
    }
}