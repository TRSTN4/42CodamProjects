#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm: public AForm
{
    private:
        std::string target;
    public:
        PresidentialPardonForm();
        PresidentialPardonForm(const std::string& target);
        PresidentialPardonForm(const PresidentialPardonForm& src);
        PresidentialPardonForm& operator=(const PresidentialPardonForm& src);
        ~PresidentialPardonForm();

        void execute(const Bureaucrat& executor) const;
};

#endif
