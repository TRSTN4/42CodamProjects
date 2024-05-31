#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(): AForm("ShrubberyCreationForm", 145, 137), target("Default") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target): AForm("ShrubberyCreationForm", 145, 137), target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& src): AForm(src), target(src.target) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(ShrubberyCreationForm& src) {
    (void)src;
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::execute(const Bureaucrat& executor) const {
    if (getSigned() == false)
        throw AForm::NotSignedException();
    else if (executor.getGrade() > getGradeToExecute())
        throw AForm::GradeTooLowException();

   std::ofstream outfile(target + "_shrubbery");
    if (outfile.is_open()) {
        outfile << "   /\\\n";
        outfile << "  /  \\\n";
        outfile << " /    \\\n";
        outfile << "/______\\\n";
        outfile << "  ||||\n";
        outfile << "  ||||\n";
        outfile.close();
    } else {
        std::cerr << "Error\nOpening file for writing.\n";
    }
}
