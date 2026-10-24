#include "Serializer.hpp"


uintptr_t Serializer::serialize (Data* ptr) {
    uintptr_t raw = (uintptr_t)ptr;
    return raw;
}

Data* Serializer::unserialize (uintptr_t raw) {
	Data *ptr = (Data *)raw;
    return ptr;
}
