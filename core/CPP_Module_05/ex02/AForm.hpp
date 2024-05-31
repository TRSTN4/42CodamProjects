#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
    private:
        const std::string name;
        bool isSigned;
        const int requiredSign;
        const int requiredExecute;
    public:
        AForm();
        AForm(const std::string& name, int requiredSign, int requiredExecute);
        AForm(const AForm& src);
        AForm& operator=(const AForm& src);
        virtual ~AForm();

        std::string getName() const;
        bool getSigned() const;
        int getGradeToSign() const;
        int getGradeToExecute() const;

        void beSigned(const Bureaucrat& bureaucrat);
        virtual void execute(const Bureaucrat& executor) const = 0;

        class GradeTooHighException: public std::exception {
            public:
                virtual const char* what() const throw() {
                    return "Grade too high";
                }
        };
        class GradeTooLowException : public std::exception {
            public:
                virtual const char* what() const throw() {
                    return "Grade too low";
                }
        };
        class NotSignedException : public std::exception {
            public:
                virtual const char* what() const throw() {
                    return "Form not signed";
                }
        };
};

std::ostream& operator<<(std::ostream& out, const AForm& src);

#endif
