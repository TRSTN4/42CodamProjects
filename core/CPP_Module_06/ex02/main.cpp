#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>
#include <random>
#include <ctime>

Base* generate() {
    static std::random_device random;
    static std::mt19937 seed(random());
    static std::uniform_int_distribution<> range(0, 2);

    int choice = range(seed);
    if (choice == 0)
        return (new A);
    else if (choice == 1)
        return (new B);
    else
        return (new C);
}

void identify(Base* p) {
    if (p == NULL) {
        std::cout << "NULL pointer parsed.\n";
        return;
    }
    if (dynamic_cast<A*>(p))
        std::cout << "A\n";
    else if (dynamic_cast<B*>(p))
        std::cout << "B\n";
    else if (dynamic_cast<C*>(p))
        std::cout << "C\n";
}

void identify(Base& p) {
    try {
        A& a = dynamic_cast<A&>(p);
        std::cout << "A\n";
        (void)a;
    } catch(const std::exception &e) {}
    try {
        B& b = dynamic_cast<B&>(p);
        std::cout << "B\n";
        (void)b;
    } catch( const std::exception &e) {}
    try {
        C& c = dynamic_cast<C&>(p);
        std::cout << "C\n";
        (void)c;
    } catch( const std::exception &e) {}
}

int main()
{
    Base* base = generate();

    std::cout << "base pointer = "; identify(base);
    std::cout << "base refrence = "; identify(*base);

    Base* bnull = NULL;
    std::cout << "bnull = "; identify(bnull);

    delete base;

    return (0);
}
