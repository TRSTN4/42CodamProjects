#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>

RPN::RPN() {}

RPN::RPN(const RPN& src) {
    *this = src;
}

RPN& RPN::operator=(const RPN& src) {
    if (this != &src)
        stack = src.stack;
    return *this;
}

RPN::~RPN() {}

void RPN::calculate(const std::string &expression) {
    std::istringstream iss(expression);
    std::string token;

    for (char ch : expression) {
        if (!std::isdigit(ch) && ch != ' ' && ch != '+' && ch != '-' && ch != '*' && ch != '/')
            throw std::runtime_error("Invalid token");
    }

    // input is "2 6 - 24 +"
    // tokens will be ['2', '6', '-', '24', '+']
    while (iss >> token) {
        // if num then push
        if (std::isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && std::isdigit(token[1])))
            stack.push(std::stoi(token));
            // after pushing '2': stack is [2]
            // after pushing '6': stack is [2, 6]
        // if token is operator then pop the nums and push result
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.size() < 2)
                throw std::runtime_error("Invalid expression");

            int b = stack.top();
            stack.pop();
            
            int a = stack.top();
            stack.pop();

            if (token == "+")
                stack.push(a + b);

            // do operation 2 - 6
            if (token == "-")
                stack.push(a - b);

            if (token == "*")
                stack.push(a * b);

            if (token == "/") {
                if (b == 0)
                    throw std::runtime_error("Division by zero");
                
                stack.push(a / b);
            }

            // after '2 - 6' stack is [-4]
            // after pushing '24' stack is [-4, 24]
            // for token '+' a = -4, b = 24
            // do -4 + 24
            // after '-4 + 24' stack is [20]
            // etc
        } else
            throw std::runtime_error("Invalid token");
    }

    // if stack has more nums then error
    if (stack.size() != 1)
        throw std::runtime_error("Invalid expression");
}

void RPN::printExpression() {
    if (stack.empty())
        throw std::runtime_error("Empty stack");

    std::cout << stack.top() << "\n";
}
