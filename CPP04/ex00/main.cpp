#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

void ft_testSound(Animal& animal) {
    std::cout << animal.getType() << " > ";
    animal.makeSound();
}

int main() {
    std::cout << "--------------- Regular Tests ---------------\n";

    Animal* animal = new Animal();
    Animal* dog = new Dog();
    Animal* cat = new Cat();

    std::cout << "\n";
    std::cout << "Animal: " << animal->getType() << " > ";
    animal->makeSound();
    std::cout << "Dog: " << dog->getType() << " > ";
    dog->makeSound();
    std::cout << "Cat: " << cat->getType() << " > ";
    cat->makeSound();
    std::cout << "\n";

    delete animal;
    delete dog;
    delete cat;

    std::cout << "\n--------------- Wrong Animal Tests ---------------\n";
    WrongAnimal* wrongAnimal = new WrongAnimal();
    WrongAnimal* wrongCat = new WrongCat();

    std::cout << "\n";
    std::cout << "WrongAnimal: " << wrongAnimal->getType() << " > ";
    wrongAnimal->makeSound();
    std::cout << "WrongCat: " << wrongCat->getType() << " > ";
    wrongCat->makeSound();
    std::cout << "\n";

    delete wrongAnimal;
    delete wrongCat;

    std::cout << "\n--------------- Array Tests ---------------\n";
    Animal* animals[4];

    animals[0] = new Dog();
    animals[1] = new Cat();
    animals[2] = new Dog();
    animals[3] = new Cat();

    for (int i = 0; i < 4; ++i) {
        std::cout << "Animal " << i << ": " << animals[i]->getType() << " > ";
        animals[i]->makeSound();
        delete animals[i];
    }

    std::cout << "\n--------------- Function Tests ---------------\n";
    Animal* animalPtr = new Animal();
    Dog* dogPtr = new Dog();
    Cat* catPtr = new Cat();

    ft_testSound(*animalPtr);
    ft_testSound(*dogPtr);
    ft_testSound(*catPtr);

    delete animalPtr;
    delete dogPtr;
    delete catPtr;

    std::cout << "\n--------------- Assignment Tests ---------------\n";
    Cat cat1;
    Cat cat2;
    Animal* cat3 = new Cat(cat1);

    cat3->makeSound();

    cat2 = cat1;

    delete cat3;

    return 0;
}
