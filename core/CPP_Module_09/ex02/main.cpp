#include "PmergeMe.hpp"
#include <string>
#include <cctype>

bool isValidInteger(const std::string& str) {
    if (str.empty())
        return false;
    for (char ch : str) {
        if (!std::isdigit(ch))
            return false;
    }
    if (std::stoi(str) <= 0)
        return false;
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "./PmergeMe <sequence>\n";
        return 1;
    }

    std::vector<int> vectorSequence;
    std::list<int> listSequence;

    try {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (!isValidInteger(arg)) {
                std::cerr << "Error: " << arg << " is not a valid positive integer.\n";
                return 1;
            }
            int num = std::stoi(arg);
            vectorSequence.push_back(num);
            listSequence.push_back(num);
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        return 1;
    }

    PmergeMe pmergeMe;

    pmergeMe.mergeInsertSort(vectorSequence);
    pmergeMe.mergeInsertSort(listSequence);

    pmergeMe.printVectorSequence();
    // pmergeMe.printListSequence();

    pmergeMe.printVectorTime();
    pmergeMe.printListTime();

    return 0;
}
