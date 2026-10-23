#include <climits>
#include <cstdlib>
#include <iostream>
#include <limits>

void convertChar (const std::string& literal, size_t len) {
    char c = 0;

    if (len == 1)
        c = literal[0];
    else
        c = literal[1];

    std::cout << "char: ";
    if (std::isprint (c)) {
        std::cout << "'" << c << "'" << std::endl;
        std::cout << "int: " << static_cast<int> (c) << std::endl;
        std::cout << "float: " << static_cast<float> (c) << std::endl;
        std::cout << "double: " << static_cast<double> (c) << std::endl;
    } else {
        std::cout << "Non displayable" << std::endl;
    }
}

void convertInt (const std::string& literal) {
    long l = std::atol (literal.c_str ());

    std::cout << "char: ";
    if (l < 0 || l > 127)
        std::cout << "impossible" << std::endl;
    else {
        if (isprint (l))
            std::cout << "'" << static_cast<char> (l) << "'" << std::endl;
        else
            std::cout << "Non displayable" << std::endl;
    }
    std::cout << "int: ";
    if (l < INT_MIN || l > INT_MAX)
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int> (l) << std::endl;

    std::cout << "float: " << static_cast<float> (l) << std::endl;
    std::cout << "double: " << static_cast<double> (l) << std::endl;
}

void convertFloat (const std::string& literal) {
    float f = std::atof (literal.c_str ());

    std::cout << "char: ";
    if (f < 0 || f > 127)
        std::cout << "impossible" << std::endl;
    else {
        if (isprint (f))
            std::cout << "'" << static_cast<char> (f) << "'" << std::endl;
        else
            std::cout << "Non displayable" << std::endl;
    }

    std::cout << "int: ";
    if (static_cast<long> (f) < INT_MIN || static_cast<long> (f) > INT_MAX)
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int> (f) << std::endl;

    std::cout << "float: ";
    if (f < std::numeric_limits<float>::min () || f > std::numeric_limits<float>::max ())
        std::cout << "impossible" << std::endl;
    else {
        std::cout << f;
        if (f == static_cast<int> (f))
            std::cout << ".0";
        std::cout << "f" << std::endl;
    }

    std::cout << "double: " << static_cast<double> (f) << std::endl;
}

void convertFloat(const std::string& literal) {
	double d = std::atof(literal.c_str());

	std::cout << "char: ";
	if (d < 0 || d > 127)
		std::cout << "impossible" << std::endl;
	else {
		if (isprint(d))
			std::cout << "'" << static_cast<char> (f) << "'" << std::endl;
		else
			std::cout << static_cast(char)d
	}
}
