#include "Harl.hpp"

#include <iostream>

bool isNotAFilter (std::string level) {
    return (level != "DEBUG" && level != "INFO" && level != "WARNING" && level != "ERROR");
}

int main (int argc, char** argv) {
    if (argc != 2 || isNotAFilter (argv[1])) {
        std::cout << "Usage: " << argv[0] << " <level>" << std::endl;
        return (1);
    }

    Harl harl;
    harl.complainFilter (argv[1]);
}
