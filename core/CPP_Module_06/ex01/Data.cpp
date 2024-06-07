#include "Data.hpp"

Data::Data(int value): data(value) {}

Data::Data(const Data& src): data(src.data) {}

Data& Data::operator=(const Data& src) {
    if (this != &src)
        data = src.data;
    return *this;
}

Data::~Data() {}

int Data::getData() const {
    return data;
}
