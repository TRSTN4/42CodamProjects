#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"

class Cat: public Animal
{
    private:
        Brain *brain;
    public:
        Cat();
        ~Cat();
        Cat(const Cat& src);
        Cat& operator=(const Cat& src);

        void makeSound() const;
        void setIdea(int index, const std::string& idea) const;
        std::string getIdea(int index) const;
};

#endif
