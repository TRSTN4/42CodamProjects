#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main( void )
{
    try {
        Bureaucrat bureaucrat("Bureaucrat", 1);
        {
            Intern someRandomIntern;
            AForm* form;

            form = someRandomIntern.makeForm("shrubbery creation", "myTree");
            delete form;
        }
        std::cout << "\n";
        {
            Intern someRandomIntern;
            AForm* form;

            form = someRandomIntern.makeForm("shrubbery creation", "myTree");
            bureaucrat.signForm(*form);
            delete form;
        }
        std::cout << "\n";
        {
            Intern someRandomIntern;
            AForm* form;

            form = someRandomIntern.makeForm("shrubbery creation", "myTree");
            bureaucrat.executeForm(*form);
            delete form;
        }
        std::cout << "\n";
        {
            Intern someRandomIntern;
            AForm* form;

            form = someRandomIntern.makeForm("shrubbery creation", "myTree");
            bureaucrat.signForm(*form);
            bureaucrat.executeForm(*form);
            delete form;
        }
        std::cout << "\n";
        {
            Intern someRandomIntern;
            AForm* form;

            form = someRandomIntern.makeForm("robotomy request", "Robotomy");
            bureaucrat.signForm(*form);
            bureaucrat.executeForm(*form);
            delete form;
        }
        std::cout << "\n";
        {
            Intern someRandomIntern;
            AForm* form;

            form = someRandomIntern.makeForm("presidential pardon", "President");
            bureaucrat.signForm(*form);
            bureaucrat.executeForm(*form);
            delete form;
        }
    } catch (std::exception &e) {
        std::cout << e.what() << "\n";
    }
    return EXIT_SUCCESS;
}
