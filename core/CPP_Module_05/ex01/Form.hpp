#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
    private:
        const std::string name;
        bool isSigned;
        const int requiredSign;
        const int requiredExecute;
    public:
        Form();
        Form(const std::string& name, int requiredSign, int requiredExecute);
        Form(const Form& src);
        Form& operator=(const Form& src);
        ~Form();

        std::string getName() const;
        bool getSigned() const;
        int getGradeToSign() const;
        int getGradeToExecute() const;

        void beSigned(const Bureaucrat& bureaucrat);

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

std::ostream& operator<<(std::ostream& out, const Form& src);

#endif
