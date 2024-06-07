#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "Data.hpp"

#include <cstdint>

class Serializer {
    private:
        Serializer();
        Serializer(const Serializer&);
        Serializer& operator=(const Serializer&);
        ~Serializer();
    public:
        static uintptr_t serialize(Data* pointer);
        static Data* deserialize(uintptr_t ui);
};

#endif
