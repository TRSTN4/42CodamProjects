#include "Form.hpp"

Form::Form(): name("Default"), requiredSign(50), requiredExecute(10) {}

Form::Form(const std::string& name, int requiredSign, int requiredExecute): name(name), requiredSign(requiredSign), requiredExecute(requiredExecute) {
    if (requiredSign < 1)
        throw Form::GradeTooHighException();
    if (requiredSign > 150)
        throw Form::GradeTooLowException();
}

Form::Form(const Form& src): name(src.getName()), requiredSign(src.getGradeToSign()), requiredExecute(src.getGradeToExecute()) {}

Form& Form::operator=(const Form& src) {
    if (this != &src)
        isSigned = src.getSigned();
    return *this;
}

Form::~Form() {}

std::string Form::getName() const {
    return name;
}

bool Form::getSigned() const {
    return isSigned;
}

int Form::getGradeToSign() const {
    return requiredSign;
}

int Form::getGradeToExecute() const {
    return requiredExecute;
}

void Form::beSigned(const Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() > requiredSign)
        throw Form::GradeTooLowException();
    isSigned = true;
}

std::ostream& operator<<(std::ostream& out, const Form& src) {
    out << "name: " << src.getName() << "\n" << "requiredSign: " << src.getGradeToSign() << "\n" << "requiredExecute: " << src.getGradeToExecute() << "\n" << "isSigned: " << src.getSigned();
    return out;
}
