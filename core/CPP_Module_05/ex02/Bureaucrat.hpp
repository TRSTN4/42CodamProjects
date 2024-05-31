#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>

#include "AForm.hpp"

class AForm;

class Bureaucrat
{
    private:
        const std::string name;
        int grade;
    public:
        Bureaucrat();
        Bureaucrat(const std::string& name, int grade);
        Bureaucrat(const Bureaucrat& src);
        Bureaucrat& operator=(const Bureaucrat& src);
        ~Bureaucrat();

        std::string getName() const;
        int getGrade() const;
        void incrementGrade();
        void decrementGrade();

        void signForm(AForm& form);
        void executeForm(const AForm& form) const;

        class GradeTooHighException: public std::exception {
            public:
                const char* what() const throw() {
                    return "Grade too high";
                }
        };
        class GradeTooLowException : public std::exception {
            public:
                const char* what() const throw() {
                    return "Grade too low";
                }
        };
};

std::ostream& operator<<(std::ostream& out, const Bureaucrat& src);

#endif
