#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat: public WrongAnimal
{
    public:
        WrongCat();
        WrongCat(std::string name);
        ~WrongCat();
        WrongCat(const WrongCat& src);
        WrongCat& operator=(const WrongCat& src);

        void makeSound() const ;
};

#endif
