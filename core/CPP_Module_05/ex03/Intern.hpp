#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"

class Intern {

public:
    Intern();
    Intern(const Intern& src);
    Intern& operator=(const Intern& src);
    ~Intern();

    AForm* makeForm(std::string name, std::string target);
};

#endif
