#include <iostream>
#include <limits>

#include "Serializer.hpp"

static void displayData (Data* data) {
    std::cout << "Data, status: " << data->status;
    std::cout << ", value: " << data->value << std::endl;
}

int main (void) {
    Data data = { std::numeric_limits<uint32_t>::max (),
        std::numeric_limits<uint32_t>::min () };

    uintptr_t raw = Serializer::serialize (&data);
    Data* ptr     = Serializer::unserialize (raw);

    if (ptr == &data)
        displayData (ptr);
    else {
        std::cout << "The addresses do not match" << std::endl;
    }
    std::cout << "Address of data = " << static_cast<void*> (&data) << std::endl;
    std::cout << "Address of ptr = " << static_cast<void*> (ptr) << std::endl;
}
