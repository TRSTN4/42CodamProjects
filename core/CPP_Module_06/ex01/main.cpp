#include "Data.hpp"
#include "Serializer.hpp"

#include <iostream>

int main() {
    Data data(42);

    std::cout << "pre-data: " << data.getData() << "\n";

    uintptr_t serializedPtr = Serializer::serialize(&data);
    Data* deserializedPtr = Serializer::deserialize(serializedPtr);

    std::cout << "post-data: " << deserializedPtr->getData() << "\n";

    if (deserializedPtr == &data)
        std::cout << "Success!\n";
    else
        std::cout << "Error\n";

    return 0;
}
