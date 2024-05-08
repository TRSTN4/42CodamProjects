#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <iostream>

#include "Brain.hpp"

class AAnimal
{
    protected:
        std::string type;
    public:
        AAnimal();
        AAnimal(std::string type);
        virtual ~AAnimal();
        AAnimal(const AAnimal& src);
        AAnimal& operator=(const AAnimal& src);

        virtual void makeSound() const = 0;
        std::string getType() const; 
};

#endif
