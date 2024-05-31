#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main( void )
{
    try {
        Bureaucrat bureaucrat("Bureaucrat", 2);

        ShrubberyCreationForm form1("MyTree");
        std::cout << "shrubbery\n";
        bureaucrat.signForm(form1);
        bureaucrat.executeForm(form1);

        RobotomyRequestForm form2("Robotomy");
        std::cout << "\nrobotomy\n";
        bureaucrat.signForm(form2);
        bureaucrat.executeForm(form2);

        PresidentialPardonForm form3("President");
        std::cout << "\npresident\n";
        bureaucrat.signForm(form3);
        bureaucrat.executeForm(form3);

        ShrubberyCreationForm form4;
        std::cout << "\ndefault shrubbery\n";
        bureaucrat.signForm(form4);
        bureaucrat.executeForm(form4);

        RobotomyRequestForm form5;
        std::cout << "\ndefault robotomy\n";
        bureaucrat.signForm(form5);
        bureaucrat.executeForm(form5);

        PresidentialPardonForm form6;
        std::cout << "\ndefault president\n";
        bureaucrat.signForm(form6);
        bureaucrat.executeForm(form6);

        Bureaucrat bureaucrat2("Bureaucrat2", 150);

        ShrubberyCreationForm form7("MyTree");
        std::cout << "\ninvalid shrubbery\n";
        bureaucrat2.signForm(form7);
        bureaucrat2.executeForm(form7);

        RobotomyRequestForm form8("Robotomy");
        std::cout << "\ninvalid robotomy\n";
        bureaucrat2.signForm(form8);
        bureaucrat2.executeForm(form8);

        PresidentialPardonForm form9("President");
        std::cout << "\ninvalid president\n";
        bureaucrat2.signForm(form9);
        bureaucrat2.executeForm(form9);

        PresidentialPardonForm form10("President2");
        PresidentialPardonForm form11(form10);
        std::cout << "\ncopy president\n";
        bureaucrat.signForm(form11);
        bureaucrat.executeForm(form11);

    } catch (std::exception &e) {
        std::cout << e.what() << "\n";
    }
    return EXIT_SUCCESS;
}
