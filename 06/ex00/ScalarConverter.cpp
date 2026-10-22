#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>

#include "ScalarConverter.hpp"

static bool isNan (double _double) {
    return (_double != _double);
}

static bool isInf(double _double) {
	return _double == std::numeric_limits<double>infinity()
}

static bool isOutOfIntRange (double _double) {
    return (_double < INT_MIN || _double > INT_MAX);
}

static bool isOutOfCharRange (double _double) {
    return (_double < 0 || _double > 127);
}

static void render_character (double _double) {
    if (isNan (_double) || isOutOfCharRange (_double)) {
        std::cout << "char: impossible" << std::endl;
        return;
    }

    char _char = static_cast<char> (_double);
    if (!std::isprint (_char)) {
        std::cout << "char: Non displayable" << std::endl;
        return;
    }

    std::cout << "char: '" << _char << "'" << std::endl;
}

static void render_int (double _double) {
    if (isNan (_double) || isOutOfIntRange (_double)) {
        std::cout << "int: impossible" << std::endl;
        return;
    }

    int _int = static_cast<int> (_double);
    std::cout << "int: " << _int << std::endl;
}

static void render_float (double _double) {
    float _float = static_cast<float> (_double);

	if (isNan(_double)) {
		std::cout << "float: "
	}
    std::cout << "float: " << _float << "f" << std::endl;
	if (_double == std::floor(_double))
}

static void render_double (double _double) {
    std::cout << std::fixed << std::setprecision (1);
    std::cout << "double: " << _double << std::endl;
}

void ScalarConverter::convert (const std::string& literal) {
    double _double = std::strtod (literal.c_str (), NULL);

    render_character (_double);
    render_int (_double);
    render_float (_double);
    render_double (_double);
}
