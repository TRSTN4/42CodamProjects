#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

#include <iostream>
#include <random>

class RobotomyRequestForm: public AForm
{
    private:
        const std::string target;
    public:
        RobotomyRequestForm();
        RobotomyRequestForm(const std::string& target);
        RobotomyRequestForm(const RobotomyRequestForm& src);
        RobotomyRequestForm &operator=(RobotomyRequestForm& src);
        ~RobotomyRequestForm();

        void execute(const Bureaucrat& executor) const;
};

#endif
