#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

class PmergeMe {
private:
    std::vector<int> vectorUnsortedSequence;
    std::vector<int> vectorSequence;

    std::list<int> listUnsortedSequence;
    std::list<int> listSequence;

    std::chrono::duration<double, std::micro> vectorDuration;
    std::chrono::duration<double, std::micro> listDuration;

    template <typename Container>
    void merge(typename Container::iterator begin, typename Container::iterator middle, typename Container::iterator end);

    template <typename Container>
    void fordJohnsonSort(Container& sequence, typename Container::iterator begin, typename Container::iterator end);

    template <typename Container>
    void printSequence(const Container& unsortedSequence, const Container& sortedSequence);

    template <typename Container>
    void printTime(const Container& sequence, const std::chrono::duration<double, std::micro>& duration, const std::string& containerName);
public:
    PmergeMe();
    PmergeMe(const PmergeMe& src);
    PmergeMe& operator=(const PmergeMe& src);
    ~PmergeMe();

    void mergeInsertSort(std::vector<int>& sequence);
    void mergeInsertSort(std::list<int>& sequence);

    void printVectorSequence();
    void printListSequence();
    void printVectorTime();
    void printListTime();
};

#endif
