#include "Harl.h"
#include <iostream>
#include <string>

int main() {
    Harl harl;

    std::string choice;
    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    while (true) {
        std::cout << "Enter your choice: ";
        
        std::getline(std::cin, choice);
        if (std::cin.fail())
            break;

        bool choiceFound = false;
        for (int i = 0; i < 4; ++i) {
            if (levels[i] == choice) {
                choiceFound = true;
                break;
            }
        }

        if (choiceFound) {
            harl.complain(choice);
        }
    }

    return 0;
}
