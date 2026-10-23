#include <iostream>
#include <string>

#include "ScalarConverter.hpp"

enum DataType {
    CHAR   = 0,
    INT    = 1,
    FLOAT  = 2,
    DOUBLE = 3,
    ERR    = 4,
};

static const std::string literalNames[6] = { "nan", "nanf", "+inf", "-inf", "+inff", "-inff" };

static bool isLiteral (const std::string& str) {
    for (int i = 0; i < 6; i++) {
        if (literalNames[i] == str)
            return true;
    }
    return false;
}

static DataType getType (const std::string& str) {
    if (isLiteral (str))
        return FLOAT;

    size_t len = str.length ();

    // CHECK FOR CHAR
    if (len == 1 && !isdigit (str[0]))
        return CHAR;
    if (len == 3 && !isdigit (str[0]) && str[0] == '\'' && str[2] == '\'')
        return CHAR;

    // CHECK FOR SIGN FOR int, float, double
    bool isSign = false;
    if (str[0] == '+' || str[0] == '-')
        isSign = true;

    // CHECK FOR INT
    size_t i;
    for (i = isSign ? 1 : 0; i < len; i++) {
        if (!isdigit (str[i]))
            break;
    }
    if (i == len)
        return INT;

    size_t dot = str.find (".");
    if (dot == std::string::npos)
        return ERR;

    // CHECK LEFT SIDE FOR ONLY NBRS
    for (i = dot - 1; i > isSign ? 1 : 0; i--) {
        if (!isdigit (str[i]))
            return ERR;
    }

    // CHECK RIGHT SIDE FOR ONLY NBRS OR 'f'
    for (i = dot + 1; i < len; i++) {
        if (!isdigit (str[i]) && (str[i] == 'f' && i != len - 1))
            return ERR;
    }

    if (str[len - 1] == 'f')
		return FLOAT;
	return DOUBLE;
}

void ScalarConverter::convert (const std::string& str) {
    std::cout << getType (str) << std::endl;
}
