#include <iostream>

static int _handle_params (int argc, char** argv);
static void _print_str_uppercase (char* str);

int main (int argc, char** argv) {
    int i;

    if (_handle_params (argc, argv) == 1)
        return (0);
    i = 1;
    while (i < argc) {
        _print_str_uppercase (argv[i]);
        i++;
    }
    std::cout << std::endl;
    return (0);
}

static size_t _strlen (char* str) {
    size_t i = 0;
    while (str[i]) {
        i++;
    }
    return (i);
}

static int _handle_params (int argc, char** argv) {
    if (argc == 1 || _strlen (argv[1]) == 0) {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
        return (1);
    }
    return (0);
}

static void _print_str_uppercase (char* str) {
    int i = 0;

    while (str[i]) {
        std::cout << (char)std::toupper ((unsigned char)str[i]);
        i++;
    }
}
