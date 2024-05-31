#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(): AForm("Robotomy Request Form", 72, 45), target("Default") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target): AForm("Robotomy Request Form", 72, 45), target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& src): AForm(src), target(src.target) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm& RobotomyRequestForm::operator=(RobotomyRequestForm& src) {
    (void)src;
    return *this;
}

void RobotomyRequestForm::execute(const Bureaucrat& executor) const {
    if (getSigned() == false)
        throw AForm::NotSignedException();
    else if (executor.getGrade() > getGradeToExecute())
        throw AForm::GradeTooLowException();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    int randomValue = dis(gen);

    if (randomValue == 1)
        std::cout << "Some drilling noises... " << target << " has been robotomized successfully 50-percent of the time.\n";
    else
        std::cout << "Robotomy failed! " << target << " is still alive.\n";
}
