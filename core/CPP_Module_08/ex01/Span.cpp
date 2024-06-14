#include "Span.hpp"
#include <algorithm>
#include <iterator>
#include <iostream> 
#include <set>
#include <stdexcept>
#include <vector>

Span::Span() {}

Span::Span(unsigned int N): N(N) {}

Span::Span(const Span& src) {
    *this = src;
}

Span& Span::operator=(Span const &src) {
    if (this != &src) {
        N = src.N;
        list = src.list;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int number) {
    if (list.size() >= N)
        throw Span::MaxNumberOfElementsReached();
    
    list.push_back(number);
}

void Span::addNumber(std::list<int>::const_iterator start, std::list<int>::const_iterator end) {
    if (std::distance(start, end) + list.size() > N)
        throw Span::MaxNumberOfElementsReached();
    
    list.insert(list.end(), start, end);
}

unsigned int Span::longestSpan() const {
    if (list.size() < 2)
        throw NotEnoughElements();
    
    int minVal = *std::min_element(list.begin(), list.end());
    int maxVal = *std::max_element(list.begin(), list.end());
    
    return maxVal - minVal;
}

unsigned int Span::shortestSpan() const {
    if (list.size() < 2)
        throw Span::NotEnoughElements();

    std::vector<int> sortedList(list.begin(), list.end());
    std::sort(sortedList.begin(), sortedList.end());

    unsigned int minSpan = std::numeric_limits<unsigned int>::max();
    for (size_t i = 1; i < sortedList.size(); ++i) {
        unsigned int span = sortedList[i] - sortedList[i - 1];
        if (span < minSpan)
            minSpan = span;
    }
    return minSpan;
}
