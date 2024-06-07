#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <limits>
#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cctype>

class ScalarConverter {
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter&);
        ScalarConverter& operator=(const ScalarConverter&);
        ~ScalarConverter();

        static bool isChar(const std::string& str);
        static bool isInt(const std::string& str);
        static bool isFloat(const std::string& str);
        static bool isDouble(const std::string& str);
        static bool isSpecial(const std::string& str);
    public:
        static void convert(const std::string& literal);
};

#endif
