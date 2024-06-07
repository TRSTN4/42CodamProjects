#include <iostream>
#include <string>
#include "Array.hpp"

void testIntegerArray() {
    std::cout << "Testing Integer Array\n";
    
    Array<int> intArray(10);
    for (unsigned int i = 0; i < intArray.size(); i++)
        intArray[i] = i;

    std::cout << "Int Array 1: " << intArray << "\n";

    Array<int> intArray2(5);
    intArray2 = intArray;

    std::cout << "Int Array 2 (after assignment): " << intArray2 << "\n";

    try {
        std::cout << "Accessing a valid index (5): " << intArray[5] << "\n";
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    try {
        std::cout << "Accessing an invalid index (" << intArray.size() + 1 << "): " << intArray[intArray.size() + 1] << "\n";
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void testFloatArray() {
    std::cout << "Testing Float Array\n";
    
    Array<float> floatArray(10);
    for (unsigned int i = 0; i < floatArray.size(); i++)
        floatArray[i] = i * 1.5;

    std::cout << "Float Array: " << floatArray << "\n";

    try {
        std::cout << "Accessing a valid index (3): " << floatArray[3] << "\n";
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    try {
        std::cout << "Accessing an invalid index (" << floatArray.size() + 1 << "): " << floatArray[floatArray.size() + 1] << "\n";
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void testStringArray() {
    std::cout << "Testing String Array\n";
    
    Array<std::string> strArray(10);
    for (unsigned int i = 0; i < strArray.size(); i++)
        strArray[i] = "String " + std::to_string(i);

    std::cout << "String Array: " << strArray << "\n";

    try {
        std::cout << "Accessing a valid index (7): " << strArray[7] << "\n";
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    try {
        std::cout << "Accessing an invalid index (" << strArray.size() + 1 << "): " << strArray[strArray.size() + 1] << "\n";
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void testEmptyArray() {
    std::cout << "Testing Empty Array\n";
    
    Array<int> emptyArray;

    std::cout << "Empty Array size: " << emptyArray.size() << "\n";

    try {
        std::cout << "Accessing index 0 in empty array: " << emptyArray[0] << "\n";
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void testCopyConstructor() {
    std::cout << "Testing Copy Constructor\n";

    Array<int> originalArray(10);
    for (unsigned int i = 0; i < originalArray.size(); i++)
        originalArray[i] = i;

    Array<int> copiedArray(originalArray);
    std::cout << "Original Array: " << originalArray << "\n";
    std::cout << "Copied Array: " << copiedArray << "\n";

    copiedArray[0] = 42;
    std::cout << "Original Array after modifying copied array: " << originalArray << "\n";
    std::cout << "Copied Array after modification: " << copiedArray << "\n";
}

int main()
{
    testIntegerArray();
    std::cout << "\n";
    testFloatArray();
    std::cout << "\n";
    testStringArray();
    std::cout << "\n";
    testEmptyArray();
    std::cout << "\n";
    testCopyConstructor();

    return 0;
}
