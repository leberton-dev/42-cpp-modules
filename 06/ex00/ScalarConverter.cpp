#include <cctype>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "ScalarConverter.hpp"

enum LiteralType {
    TYPE_CHAR    = 0,
    TYPE_INT     = 1,
    TYPE_FLOAT   = 2,
    TYPE_DOUBLE  = 3,
    TYPE_INVALID = 4,
};

static const std::string pseudoLiterals[6] = { "nan", "nanf", "+inf", "-inf",
    "+inff", "-inff" };

static bool isPseudoLiteral (const std::string& literal) {
    for (int i = 0; i < 6; i++) {
        if (pseudoLiterals[i] == literal)
            return true;
    }
    return false;
}

static LiteralType detectType (const std::string& literal) {
    if (literal.empty ())
        return TYPE_INVALID;

    if (isPseudoLiteral (literal))
        return TYPE_FLOAT;

    size_t len = literal.length ();

    // CHECK FOR CHAR

    if (len == 1 && !isdigit (literal[0]))
        return TYPE_CHAR;
    if (len == 3 && literal[0] == '\'' && literal[2] == '\'')
        return TYPE_CHAR;

    // CHECK FOR SIGN FOR int, float, double
    size_t digitStart = 0;
    if (literal[0] == '+' || literal[0] == '-')
        digitStart = 1;

    // CHECK FOR INT
    size_t i;
    for (i = digitStart; i < len; i++) {
        if (!isdigit (literal[i]))
            break;
    }
    if (i == len)
        return TYPE_INT;

    size_t dotPos = literal.find (".");
    if (dotPos == std::string::npos || dotPos == digitStart || dotPos + 1 == len)
        return TYPE_INVALID;

    // CHECK LEFT SIDE FOR ONLY NBRS
    for (i = digitStart; i < dotPos; i++) {
        if (!isdigit (literal[i]))
            return TYPE_INVALID;
    }

    // CHECK RIGHT SIDE FOR ONLY NBRS OR 'f'
    for (i = dotPos + 1; i < len; i++) {
        if (literal[i] == 'f' && i == len - 1) {
            if (dotPos == i - 1)
                return TYPE_INVALID;
            continue;
        }
        if (!isdigit (literal[i]))
            return TYPE_INVALID;
    }

    if (literal[len - 1] == 'f')
        return TYPE_FLOAT;
    return TYPE_DOUBLE;
}

static std::string withDecimalPoint (double d) {
    std::ostringstream oss;
    oss << d;
    std::string s = oss.str ();
    if (s.find (".") == std::string::npos && s.find ('e') == std::string::npos)
        s += ".0";
    return s;
}

static void printChar (double value) {
    std::cout << "char: ";
    if (value != value || value < 0 || value > 127)
        std::cout << "impossible" << std::endl;
    else if (!std::isprint (static_cast<int> (value)))
        std::cout << "Non displayable" << std::endl;
    else
        std::cout << "'" << static_cast<char> (value) << "'" << std::endl;
}

static void printInt (double value) {
    std::cout << "int: ";
    if (value != value || value < INT_MIN || value > INT_MAX)
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int> (value) << std::endl;
}

static void printFloat (double value) {
    const double inf = std::numeric_limits<float>::infinity ();
    const double max = std::numeric_limits<float>::max ();

    std::cout << "float: ";
    if (value != value)
        std::cout << "nanf" << std::endl;
    else if (value == inf)
        std::cout << "+inff" << std::endl;
    else if (value == -inf)
        std::cout << "-inff" << std::endl;
    else if (value > max || value < -max)
        std::cout << "impossible" << std::endl;
    else
        std::cout << withDecimalPoint (static_cast<float> (value)) << "f" << std::endl;
}
static void printDouble (double value) {
    const double inf = std::numeric_limits<double>::infinity ();

    std::cout << "double: ";
    if (value != value)
        std::cout << "nan" << std::endl;
    else if (value == inf)
        std::cout << "+inf" << std::endl;
    else if (value == -inf)
        std::cout << "-inf" << std::endl;
    else
        std::cout << withDecimalPoint (value) << std::endl;
}

static void convertFromChar (const std::string& literal) {
    char c;

    c               = literal.length () == 1 ? literal[0] : literal[1];
    double asDouble = static_cast<double> (c);
    printChar (asDouble);
    printInt (asDouble);
    printFloat (asDouble);
    printDouble (asDouble);
}

static void convertFromInt (const std::string& literal) {
    long l = std::strtol (literal.c_str (), NULL, 10);
    double asDouble;

    if (l > INT_MAX || l < INT_MIN)
        asDouble = static_cast<double> (l);
    else {
        int i    = static_cast<int> (l);
        asDouble = static_cast<double> (i);
    }
    printChar (asDouble);
    printInt (asDouble);
    printFloat (asDouble);
    printDouble (asDouble);
}

static void convertFromFloat (const std::string& literal) {
    float f         = static_cast<float> (std::strtod (literal.c_str (), NULL));
    double asDouble = static_cast<double> (f);

    printChar (asDouble);
    printInt (asDouble);
    printFloat (asDouble);
    printDouble (asDouble);
}

static void convertFromDouble (const std::string& literal) {
    double d = std::strtod (literal.c_str (), NULL);

    printChar (d);
    printInt (d);
    printFloat (d);
    printDouble (d);
}

void ScalarConverter::convert (const std::string& literal) {
    switch (detectType (literal)) {
    case TYPE_CHAR: convertFromChar (literal); break;
    case TYPE_INT: convertFromInt (literal); break;
    case TYPE_FLOAT: convertFromFloat (literal); break;
    case TYPE_DOUBLE: convertFromDouble (literal); break;
    case TYPE_INVALID: std::cout << "error: invalid literal" << std::endl;
    }
}
