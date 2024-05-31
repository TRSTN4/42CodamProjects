#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(): AForm("PresidentialPardonForm", 25, 5), target("Default") {}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target): AForm("PresidentialPardonForm", 25, 5), target(target) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& src): AForm(src), target(src.target) {}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& src) {
    (void)src;
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {}

void PresidentialPardonForm::execute(const Bureaucrat& executor) const {
    if (getSigned() == false)
        throw AForm::NotSignedException();
    else if (executor.getGrade() > getGradeToExecute())
        throw AForm::GradeTooLowException();

    std::cout << target << " has been pardoned by Zaphod Beeblebrox.\n";
}
