#include "easyfind.hpp"
#include <vector>
#include <list>
#include <deque>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::list<int> lst = {1, 2, 3, 4, 5};
    std::deque<int> deq = {1, 2, 3, 4, 5};

    try {
        std::cout << "Is 3 in the vector?\n";
        auto itVec = easyfind(vec, 3);
        std::cout << "Yes, found: " << *itVec << "\n";
    } catch (const NotFoundException& e) {
        std::cout << "No, not found.\n";
    }

    try {
        std::cout << "Is 6 in the vector?\n";
        auto itVec = easyfind(vec, 6);
        std::cout << "Yes, found: " << *itVec << "\n";
    } catch (const NotFoundException& e) {
        std::cout << "No, not found.\n";
    }

    try {
        std::cout << "Is 2 in the list?\n";
        auto itList = easyfind(lst, 2);
        std::cout << "Yes, found: " << *itList << "\n";
    } catch (const NotFoundException& e) {
        std::cout << "No, not found.\n";
    }

    try {
        std::cout << "Is 7 in the list?\n";
        auto itList = easyfind(lst, 7);
        std::cout << "Yes, found: " << *itList << "\n";
    } catch (const NotFoundException& e) {
        std::cout << "No, not found.\n";
    }

    try {
        std::cout << "Is 1 in the deque?\n";
        auto itDeq = easyfind(deq, 1);
        std::cout << "Yes, found: " << *itDeq << "\n";
    } catch (const NotFoundException& e) {
        std::cout << "No, not found.\n";
    }

    try {
        std::cout << "Is 9 in the deque?\n";
        auto itDeq = easyfind(deq, 9);
        std::cout << "Yes, found: " << *itDeq << "\n";
    } catch (const NotFoundException& e) {
        std::cout << "No, not found.\n";
    }

    return 0;
}
