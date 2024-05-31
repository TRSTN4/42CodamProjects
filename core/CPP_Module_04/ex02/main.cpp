#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int main( void )
{
    // AAnimal* animal = new AAnimal();
    
    std::cout << "--------------- Regular Tests ---------------\n";

    AAnimal* dog = new Dog();
    AAnimal* cat = new Cat();

    std::cout << "\n";
    std::cout << "Dog: " << dog->getType() << " > ";
    dog->makeSound();
    std::cout << "Cat: " << cat->getType() << " > ";
    cat->makeSound();
    std::cout << "\n";

    delete dog;
    delete cat;

    std::cout << "\n--------------- Array Tests ---------------\n";
    AAnimal* animals[4];

    animals[0] = new Dog();
    animals[1] = new Cat();
    animals[2] = new Dog();
    animals[3] = new Cat();

    for (int i = 0; i < 4; ++i) {
        std::cout << "Animal " << i << ": " << animals[i]->getType() << " > ";
        animals[i]->makeSound();
        delete animals[i];
    }

    return 0;
}
