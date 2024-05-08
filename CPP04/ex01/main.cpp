#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

void ft_testSound(Animal& animal) {
    std::cout << animal.getType() << " > ";
    animal.makeSound();
}

int main() {
    std::cout << "\n--------------- Deep Copy Test ---------------\n";
    Dog originalDog;
    originalDog.setIdea(0, "Original idea from originalDog");

    std::cout << "Creating copyDog...\n";
    {
        Dog copyDog = originalDog;
        std::cout << "copyDog created\n";
        copyDog.setIdea(0, "Modified idea in copyDog");

        std::cout << "originalDog's first idea: " << originalDog.getIdea(0) << "\n";
        std::cout << "copyDog's first idea: " << copyDog.getIdea(0) << "\n";
    }
    std::cout << "copyDog destroyed\n";
    std::cout << "originalDog's first idea after copyDog is destroyed: " << originalDog.getIdea(0) << "\n";
    
    std::cout << "\n--------------- Array Test ---------------\n";
    const int numAnimals = 10;
    Animal* animals[numAnimals];

    for (int i = 0; i < numAnimals; ++i) {
        if (i < numAnimals / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    for (int i = 0; i < numAnimals; ++i) {
        std::cout << "Animal " << i << ": " << animals[i]->getType() << " > ";
        animals[i]->makeSound();
    }

    for (int i = 0; i < numAnimals; ++i) {
        delete animals[i];
    }

    std::cout << "\n--------------- Assignment Tests ---------------\n";
    Cat cat1;
    Cat cat2;
    Animal* cat3 = new Cat(cat1);

    cat3->makeSound();

    cat2 = cat1;

    delete cat3;

    return 0;
}
