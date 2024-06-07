#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter&) {}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter&) {
    return *this;
}

ScalarConverter::~ScalarConverter() {}

bool ScalarConverter::isChar(const std::string& str) {
    if (str.length() == 1 && std::isprint(str[0]) && !std::isdigit(str[0]))
        return true;
    return false;
}

bool ScalarConverter::isInt(const std::string& str) {
    try {
        std::size_t pos;
        std::stoi(str, &pos);
        if (pos == str.size())
            return true;    
    } catch(const std::exception &e) {
        return false;
    }
    return false;
}

bool ScalarConverter::isFloat(const std::string& str) {
    try {
        std::size_t pos;
        std::stof(str, &pos);
        if (pos == str.size() - 1 && str.back() == 'f')
            return true;
    } catch(const std::exception &e) {
        return false;
    }
    return false;
}

bool ScalarConverter::isDouble(const std::string& str) {
    try {
        std::size_t pos;
        std::stod(str, &pos);
        if (pos == str.size())
            return true;
    } catch(const std::exception &e) {
        return false;
    }
    return false;
}

bool ScalarConverter::isSpecial(const std::string& str) {
    if (str == "nan" || str == "nanf" || str == "+inf" || str == "+inff" || str == "-inf" || str == "-inff")
        return true;
    return false;
}

void ScalarConverter::convert(const std::string& str) {
    char conv_char;
    int conv_int;
    float conv_float;
    double conv_double;

    try {
        if (isSpecial(str)) {
            if (str == "nan" || str == "nanf") {
                conv_float = std::numeric_limits<float>::quiet_NaN();
                conv_double = std::numeric_limits<double>::quiet_NaN();
            } else if (str == "+inf" || str == "+inff") {
                conv_float = std::numeric_limits<float>::infinity();
                conv_double = std::numeric_limits<double>::infinity();
            } else if (str == "-inf" || str == "-inff") {
                conv_float = -std::numeric_limits<float>::infinity();
                conv_double = -std::numeric_limits<double>::infinity();
            }

            std::cout << "char: impossible\n";
            std::cout << "int: impossible\n";
            if (str == "nan")
                std::cout << "float: nanf\n";
            else if (str == "+inf")
                std::cout << "float: +inff\n";
            else if (str == "-inf")
                std::cout << "float: -inff\n";
            else
                std::cout << "float: " << str << "\n";

            if (str == "nanf")
                std::cout << "double: nan\n";
            else if (str == "+inff")
                std::cout << "double: +inf\n";
            else if (str == "-inff")
                std::cout << "double: -inf\n";
            else
                std::cout << "double: " << str << "\n";
        } else if (isChar(str)) {
            conv_char = str[0];
            conv_int = static_cast<int>(conv_char);
            conv_float = static_cast<float>(conv_char);
            conv_double = static_cast<double>(conv_char);

            std::cout << "char: '" << conv_char << "'\n";
            std::cout << "int: " << conv_int << "\n";
            std::cout << "float: " << conv_float << ".0f\n";
            std::cout << "double: " << conv_double << ".0\n";
        } else if (isInt(str)) {
            conv_int = std::stoi(str);
            conv_char = static_cast<char>(conv_int);
            conv_float = static_cast<float>(conv_int);
            conv_double = static_cast<double>(conv_int);

            if (conv_int < 32 || conv_int > 126)
                std::cout << "char: Non displayable\n";
            else
                std::cout << "char: '" << conv_char << "'\n";
            std::cout << "int: " << conv_int << "\n";
            std::cout << "float: " << conv_float << ".0f\n";
            std::cout << "double: " << conv_double << ".0\n";
        } else if (isFloat(str)) {
            conv_float = std::stof(str);
            conv_int = static_cast<int>(conv_float);
            conv_char = static_cast<char>(conv_float);
            conv_double = static_cast<double>(conv_float);

            if (conv_int < 32 || conv_int > 126)
                std::cout << "char: Non displayable\n";
            else
                std::cout << "char: '" << conv_char << "'\n";
            std::cout << "int: " << conv_int << "\n";
            std::cout << "float: " << conv_float << "f\n";
            std::cout << "double: " << conv_double << "f\n";
        } else if (isDouble(str)) {
            conv_double = std::stod(str);
            conv_int = static_cast<int>(conv_double);
            conv_char = static_cast<char>(conv_double);
            conv_float = static_cast<float>(conv_double);

            if (conv_int < 32 || conv_int > 126)
                std::cout << "char: Non displayable\n";
            else
                std::cout << "char: '" << conv_char << "'\n";
            std::cout << "int: " << conv_int << "\n";
            std::cout << "float: " << conv_float << "f\n";
            std::cout << "double: " << conv_double << "\n";
        } else
            throw std::invalid_argument("Unknown type\n");
    } catch (const std::exception& e) {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: impossible\n";
        std::cout << "double: impossible\n";
    }
}
