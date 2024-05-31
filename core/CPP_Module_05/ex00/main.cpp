#include "Bureaucrat.hpp"

int main() {
    std::cout << "--- valid init ---\n";
    Bureaucrat bureaucrat1("Bureaucrat", 50);
    std::cout << bureaucrat1 << "\n";

    std::cout << "--- valid increment ---\n";
    Bureaucrat bureaucrat2("Bureaucrat", 50);
    std::cout << bureaucrat2 << "\n";
    bureaucrat2.incrementGrade();
    std::cout << bureaucrat2 << "\n";

    std::cout << "--- valid decrement ---\n";
    Bureaucrat bureaucrat3("Bureaucrat", 50);
    std::cout << bureaucrat3 << "\n";
    bureaucrat3.decrementGrade();
    std::cout << bureaucrat3 << "\n";

    std::cout << "--- too high increment ---\n";
    try {
        Bureaucrat bureaucrat4("Bureaucrat", 1);
        std::cout << bureaucrat4 << "\n";
        bureaucrat4.incrementGrade();
    } catch (const Bureaucrat::GradeTooHighException &e) {
        std::cout << e.what() << "\n";
    }

    std::cout << "--- too high ---\n";
    try {
        Bureaucrat bureaucrat5("Bureaucrat", 0);
    } catch (const Bureaucrat::GradeTooHighException &e) {
        std::cout << e.what() << "\n";
    }

    std::cout << "--- too low decrement ---\n";
    try {
        Bureaucrat bureaucrat6("Bureaucrat", 150);
        std::cout << bureaucrat6 << "\n";
        bureaucrat6.decrementGrade();
    } catch (const Bureaucrat::GradeTooLowException &e) {
        std::cout << e.what() << "\n";
    }

    std::cout << "--- too low ---\n";
    try {
        Bureaucrat bureaucrat7("Bureaucrat", 151);
    } catch (const Bureaucrat::GradeTooLowException &e) {
        std::cout << e.what() << "\n";
    }

    std::cout << "--- copy ---\n";
    Bureaucrat bureaucrat8(bureaucrat1);
    std::cout << bureaucrat8 << "\n";

    std::cout << "--- copy assignment ---\n";
    Bureaucrat bureaucrat9;
    bureaucrat9 = bureaucrat1;
    std::cout << bureaucrat9 << "\n";

    return 0;
}
