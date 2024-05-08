#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"

class Dog: public Animal
{
    private:
        Brain *brain;
    public:
        Dog();
        ~Dog();
        Dog(const Dog& src);
        Dog& operator=(const Dog& src);

        void makeSound() const;
        void setIdea(int index, const std::string& idea) const;
        std::string getIdea(int index) const;
};

#endif
