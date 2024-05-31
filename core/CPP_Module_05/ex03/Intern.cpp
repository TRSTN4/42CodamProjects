#include "Intern.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern() {}

Intern::Intern(const Intern& src) {
    *this = src;
}

Intern& Intern::operator=(const Intern& src) {
    (void) src;
    return (*this);
}

Intern::~Intern() {}

AForm* Intern::makeForm(std::string name, std::string target) {
    std::string formNames[] = {
        "robotomy request",
        "presidential pardon",
        "shrubbery creation"
    };

    AForm* forms[] = {
        new RobotomyRequestForm(target),
        new PresidentialPardonForm(target),
        new ShrubberyCreationForm(target)
    };

    for (int i = 0; i < 3; i++) {
        if (name == formNames[i]) {
            std::cout << "Intern creates " << name << "\n";
            for (int j = 0; j < 3; j++) {
                if (i != j)
                    delete forms[j];
            }
            return forms[i];
        }
    }
    std::cout << "Error\nForm " << name << " doesn't exist.\n";
    for (int i = 0; i < 3; i++)
        delete forms[i];
    return nullptr;
}
