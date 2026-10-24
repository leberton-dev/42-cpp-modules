#include <cstdlib>
#include <ctime>

#include "Base.hpp"

int main (void) {
    std::srand (std::time (NULL));
    Base* p = generate ();

    identify (p);
    identify (*p);
    delete p;

    return 0;
}
