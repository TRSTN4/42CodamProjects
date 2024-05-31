#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): name("Default"), grade(150) {}

Bureaucrat::Bureaucrat(const std::string& name, int grade): name(name), grade(grade) {
    if (grade < 1) {
        throw Bureaucrat::GradeTooHighException();
    }
    if (grade > 150) {
        throw Bureaucrat::GradeTooLowException();
    }
}

Bureaucrat::Bureaucrat(const Bureaucrat& src): name(src.name), grade(src.grade) {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& src) {
    if (this != &src)
        grade = src.getGrade();
    return *this;
}

Bureaucrat::~Bureaucrat() {}

std::string Bureaucrat::getName() const {
    return name;
}

int Bureaucrat::getGrade() const {
    return grade;
}

void Bureaucrat::incrementGrade() {
    if ((grade - 1) < 1) {
        throw Bureaucrat::GradeTooHighException();
    }
    grade--;
}

void Bureaucrat::decrementGrade() {
    if ((grade + 1) > 150) {
        throw Bureaucrat::GradeTooLowException();
    }
    grade++;
}

std::ostream& operator<<(std::ostream& out, const Bureaucrat& src) {
    out << src.getName() << ", bureaucrat grade " << src.getGrade();
    return out;
}

void Bureaucrat::executeForm(const AForm& form) const {
    try {
        form.execute(*this);
    } catch (std::exception& e) {
        std::cout << name << " couldn't execute " << form.getName() << " because " << e.what() << "\n";
    }
}

void Bureaucrat::signForm(AForm& form) {
    try {
        form.beSigned(*this);
        std::cout << name << " signed " << form.getName() << "\n";
    } catch (AForm::GradeTooLowException &e) {
        std::cout << name << " couldn't sign " << form.getName() << " because " << e.what() << "\n";
    }
}
