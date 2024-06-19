#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <string>
#include <iostream>

class RPN {
    private:
        std::stack<int> stack;
    public:
        RPN();
        RPN(const RPN&);
        RPN& operator=(const RPN&);
        ~RPN();

        void calculate(const std::string& expression);
        void printExpression();
};

#endif
