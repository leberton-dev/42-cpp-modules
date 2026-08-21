#include "Harl.hpp"
#include <cstdlib>

int main (int argc, char** argv) {
    if (argc != 2)
        return (EXIT_FAILURE);
    Harl harl;
    harl.complain (std::string (argv[1]));
}
