#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"

#include <fstream>

class ShrubberyCreationForm: public AForm {
    private:
        const std::string target;
    public:
        ShrubberyCreationForm();
        ShrubberyCreationForm(const std::string& target);
        ShrubberyCreationForm(const ShrubberyCreationForm& src);
        ShrubberyCreationForm& operator=(ShrubberyCreationForm& src);
        ~ShrubberyCreationForm();

        void execute(const Bureaucrat& executor) const;
};

#endif
