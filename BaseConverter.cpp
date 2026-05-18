#include "BaseConverter.h"
#include "Parser.h"
#include "Formatter.h"
QString BaseConverter::convert(const QString& input, int p, int q) {
    try {
        BigFraction f = Parser::parse(input, p);
        f.output();
        return Formatter::toBase(f, q);
    } catch (const char* error) {
        return error;
    }


}