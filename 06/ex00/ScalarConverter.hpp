#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <string>

class ScalarConverter {
    public:
    static void convert (const std::string& literal);

    private:
    ScalarConverter ();
    ScalarConverter (const ScalarConverter& s);
    ScalarConverter& operator= (const ScalarConverter& e);
    ~ScalarConverter ();
};

#endif
