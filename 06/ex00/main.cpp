#include <iostream>

#include "ScalarConverter.hpp"


// static void printSection (const std::string& name) {
//     std::cout << std::endl << "===== [" << name << "] =====" << std::endl;
// }
//
// static void runTest (const std::string& input) {
//     std::cout << "----- test " << input << " -----" << std::endl;
//     ScalarConverter::convert (input);
// }
//
// const std::string inCases[] = { "0", "65", "-42", "2147483647", "2147483648", "-2147483649" };
//
// const std::string floatCases[] = { "0.0f", "-4.2f", "4.2f", "65.0f" };
//
// const std::string doubleCases[] = { "0.0", "-4.2", "4.2", "65.0",
//     "99999999999999999999999999999999999999999.0" };
//
// const std::string pseudoLiteralCases[] = { "nan", "nanf", "+inf", "-inf", "+inff", "-inff" };
//
// const std::string invalidCases[] = {
//     "",
//     "1.2.3",
//     "65f",
//     "abc",
//     "12abc",
//     "++1",
//     "--1",
//     "1.f",
//     ".5",
//     "3.4e39",
// };
//
// static void test_suite (const std::string params[], size_t size) {
//     for (size_t i = 0; i < size; i++)
//         runTest (params[i]);
// }

#define ARRAY_SIZE(arr) (sizeof (arr) / sizeof ((arr)[0]))

int main (int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "error: argument count must be 2" << std::endl;
        std::cerr << "usage: " << argv[0] << " ARGUMENT" << std::endl;
        return 1;
    }
    ScalarConverter::convert (argv[1]);

    // (void)argc;
    // (void)argv;
    //
    // printSection ("TEST INTEGERS");
    // test_suite (inCases, ARRAY_SIZE (inCases));
    //
    // printSection ("TEST FLOAT");
    // test_suite (floatCases, ARRAY_SIZE (floatCases));
    //
    // printSection ("TEST DOUBLE");
    // test_suite (doubleCases, ARRAY_SIZE (doubleCases));
    //
    // printSection ("TEST LITERALS");
    // test_suite (pseudoLiteralCases, ARRAY_SIZE (pseudoLiteralCases));
    //
    // printSection ("TEST ERRORS");
    // test_suite (invalidCases, ARRAY_SIZE (invalidCases));

    return 0;
}
