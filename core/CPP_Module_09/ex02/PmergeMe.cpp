#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& src) {
    *this = src;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& src) {
    if (this != &src) {
        vectorUnsortedSequence = src.vectorUnsortedSequence;
        listUnsortedSequence = src.listUnsortedSequence;

        vectorSequence = src.vectorSequence;
        listSequence = src.listSequence;

        vectorDuration = src.vectorDuration;
        listDuration = src.listDuration;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}


// merge call with [27, 38, 43] and [3, 9, 10, 82]:
// left as [27, 38, 43]
// right as [3, 9, 10, 82]
// Merging steps:
// Compare 27 and 3: 3 is smaller, add to sequence.
// Compare 27 and 9: 9 is smaller, add to sequence.
// Compare 27 and 10: 10 is smaller, add to sequence.
// Compare 27 and 82: 27 is smaller, add to sequence.
// Compare 38 and 82: 38 is smaller, add to sequence.
// Compare 43 and 82: 43 is smaller, add to sequence.
// Add remaining 82 to sequence.

template <typename Container>
void PmergeMe::merge(typename Container::iterator begin, typename Container::iterator middle, typename Container::iterator end) {
    // creates two temp sequences for left and right
    Container left(begin, middle);
    Container right(middle, end);

    // iters for left, right, and original sequences
    auto itLeft = left.begin();
    auto itRight = right.begin();
    auto itSeq = begin;

    // merge left and right sequences
    while (itLeft != left.end() && itRight != right.end()) {
        if (*itLeft <= *itRight) {
            *itSeq = *itLeft;
            ++itLeft;
        } else {
            *itSeq = *itRight;
            ++itRight;
        }
        ++itSeq;
    }

    // copy remaining stuff from the left sequence
    while (itLeft != left.end()) {
        *itSeq = *itLeft;
        ++itLeft;
        ++itSeq;
    }

    // copy remaining stuff from the right sequence
    while (itRight != right.end()) {
        *itSeq = *itRight;
        ++itRight;
        ++itSeq;
    }
}

template <typename Container>
void PmergeMe::fordJohnsonSort(Container& sequence, typename Container::iterator begin, typename Container::iterator end) {
    if (std::distance(begin, end) <= 1)
        return;

    auto middle = std::next(begin, std::distance(begin, end) / 2);

    fordJohnsonSort(sequence, begin, middle);
    fordJohnsonSort(sequence, middle, end);

    merge<Container>(begin, middle, end);
}

void PmergeMe::mergeInsertSort(std::vector<int>& sequence) {
    vectorUnsortedSequence = sequence;

    auto start = std::chrono::high_resolution_clock::now();

    vectorSequence = sequence;

    fordJohnsonSort(vectorSequence, vectorSequence.begin(), vectorSequence.end());

    auto end = std::chrono::high_resolution_clock::now();

    vectorDuration = end - start;
}

void PmergeMe::mergeInsertSort(std::list<int>& sequence) {
    listUnsortedSequence = sequence;
    auto start = std::chrono::high_resolution_clock::now();

    listSequence.assign(sequence.begin(), sequence.end());

    fordJohnsonSort(listSequence, listSequence.begin(), listSequence.end());

    auto end = std::chrono::high_resolution_clock::now();

    listDuration = end - start;
}

template <typename Container>
void PmergeMe::printSequence(const Container& unsortedSequence, const Container& sortedSequence) {
    std::cout << "Before:";
    for (const int& num : unsortedSequence)
        std::cout << " " << num;
    std::cout << "\n";

    std::cout << "After:";
    for (const int& num : sortedSequence)
        std::cout << " " << num;
    std::cout << "\n";
}

template <typename Container>
void PmergeMe::printTime(const Container& sequence, const std::chrono::duration<double, std::micro>& duration, const std::string& containerName) {
    std::cout << "Time to process a range of " << sequence.size() << " elements with " << containerName << " : " << duration.count() << " us\n";
}

void PmergeMe::printVectorSequence() {
    printSequence(vectorUnsortedSequence, vectorSequence);
}

void PmergeMe::printListSequence() {
    printSequence(listUnsortedSequence, listSequence);
}

void PmergeMe::printVectorTime() {
    printTime(vectorSequence, vectorDuration, "std::vector");
}

void PmergeMe::printListTime() {
    printTime(listSequence, listDuration, "std::list");
}
