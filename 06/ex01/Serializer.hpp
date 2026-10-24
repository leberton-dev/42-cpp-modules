#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>
#include <string>

struct Data {
	uint32_t	status;
	uint32_t	value;
};

class Serializer {
    public:
    static uintptr_t serialize (Data* ptr);
    static Data* unserialize (uintptr_t raw);

    private:
    Serializer ();
    Serializer (const Serializer& other);
    Serializer operator= (const Serializer& other);
    ~Serializer ();
};

#endif
