#include "AForm.hpp"

AForm::AForm(): name("Default"), requiredSign(50), requiredExecute(10) {}

AForm::AForm(const std::string& name, int requiredSign, int requiredExecute): name(name), requiredSign(requiredSign), requiredExecute(requiredExecute) {
    if (requiredSign < 1)
        throw AForm::GradeTooHighException();
    if (requiredSign > 150)
        throw AForm::GradeTooLowException();
}

AForm::AForm(const AForm& src): name(src.getName()), requiredSign(src.getGradeToSign()), requiredExecute(src.getGradeToExecute()) {}

AForm& AForm::operator=(const AForm& src) {
    if (this != &src)
        isSigned = src.getSigned();
    return *this;
}

AForm::~AForm() {}

std::string AForm::getName() const {
    return name;
}

bool AForm::getSigned() const {
    return isSigned;
}

int AForm::getGradeToSign() const {
    return requiredSign;
}

int AForm::getGradeToExecute() const {
    return requiredExecute;
}

void AForm::beSigned(const Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() > requiredSign)
        throw AForm::GradeTooLowException();
    isSigned = true;
}

std::ostream& operator<<(std::ostream& out, const AForm& src) {
    out << "name: " << src.getName() << "\n" << "requiredSign: " << src.getGradeToSign() << "\n" << "requiredExecute: " << src.getGradeToExecute() << "\n" << "isSigned: " << src.getSigned();
    return out;
}
