#ifndef CAT_HPP
#define CAT_HPP

#include "AAnimal.hpp"

class Cat: public AAnimal
{
    private:
        Brain *brain;
    public:
        Cat();
        ~Cat();
        Cat(const Cat& src);
        Cat& operator=(const Cat& src);

        void makeSound() const;
};

#endif
