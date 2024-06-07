#include "Serializer.hpp"

Serializer::Serializer() {}

Serializer::Serializer(const Serializer&) {}

Serializer& Serializer::operator=(const Serializer&) {
    return *this;
}

Serializer::~Serializer() {}

uintptr_t Serializer::serialize(Data *pointer) {
	return reinterpret_cast<uintptr_t>(pointer);
}

Data* Serializer::deserialize(uintptr_t ui) {
    return reinterpret_cast<Data*>(ui);
}
