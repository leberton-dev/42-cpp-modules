#include <iostream>

#include "ScalarConverter.hpp"


int main (int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "error: argument count must be 2" << std::endl;
        std::cerr << "usage: " << argv[0] << " ARGUMENT" << std::endl;
        return 1;
    }
    ScalarConverter::convert (argv[1]);
    return 0;
}
