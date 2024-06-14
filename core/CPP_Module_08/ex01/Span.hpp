#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <list>
#include <exception>

class Span
{
    private:
        unsigned int N;
        std::list<int> list;

        Span();
    public:
        Span(unsigned int N);
        Span(const Span& src);
        Span& operator=(const Span& src);
        ~Span();

        void addNumber(int number);
        void addNumber(std::list<int>::const_iterator start, std::list<int>::const_iterator end);
        
        unsigned int shortestSpan() const;
        unsigned int longestSpan() const;

        class MaxNumberOfElementsReached: public std::exception {
            public:
                MaxNumberOfElementsReached() = default;
                MaxNumberOfElementsReached(const MaxNumberOfElementsReached&) = default;
                MaxNumberOfElementsReached& operator=(const MaxNumberOfElementsReached&) = delete;
                ~MaxNumberOfElementsReached() noexcept override = default;

                const char* what() const noexcept override {
                    return "Max number of elements reached";
                }
        };
        class NotEnoughElements: public std::exception {
            public:
                NotEnoughElements() = default;
                NotEnoughElements(const NotEnoughElements&) = default;
                NotEnoughElements& operator=(const NotEnoughElements&) = delete;
                ~NotEnoughElements() noexcept override = default;

                const char* what() const noexcept override {
                    return "Not enough elements";
                }
        };
};

#endif
