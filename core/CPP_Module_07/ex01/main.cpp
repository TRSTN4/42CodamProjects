#include "iter.hpp"

#include <string>
#include <iostream>

int main()
{
    int intArray[] = {1, 2, 3, 4, 5};
    char charArray[] = {'a', 'b', 'c', 'd', 'e'};
    std::string stringArray[] = {"one", "two", "three", "four", "five"};
    bool boolArray[] = {true, false, false, true, true, true, true, false};

    std::cout << "intArray:\n";
    iter(intArray, (std::end(intArray) - std::begin(intArray)), &elementPrinter);

    std::cout << "\ncharArray:\n";
    iter(charArray, (std::end(charArray) - std::begin(charArray)), &elementPrinter);

    std::cout << "\nstringArray:\n";
    iter(stringArray, (std::end(stringArray) - std::begin(stringArray)), &elementPrinter);

    std::cout << "\nboolArray:\n";
    iter(boolArray, (std::end(boolArray) - std::begin(boolArray)), &elementPrinter);

    return 0;
}
