#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>
#include <list>
#include <deque>

class NotFoundException: public std::exception {
    public:
        NotFoundException() = default;
        NotFoundException(const NotFoundException&) = default;
        NotFoundException& operator=(const NotFoundException&) = delete;
        ~NotFoundException() noexcept override = default;

        const char* what() const noexcept override {
            return "Element not found";
        }
};

template <typename T>
typename T::iterator easyfind(T& container, int toFind);

#include "easyfind.tpp"

#endif
