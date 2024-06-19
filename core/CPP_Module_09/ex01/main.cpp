#include "RPN.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "./RPN <expression>\n";
        return 1;
    }

    try {
        RPN rpn;
        rpn.calculate(argv[1]);
        rpn.printExpression();
    } catch (const std::exception& e) {
        std::cout << "Error\n" << e.what() << "\n";
    }

    return 0;
}
