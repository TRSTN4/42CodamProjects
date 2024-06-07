#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <exception>

template <typename T>
class Array {
    private:
        T* array;
        unsigned int length;
    public:
        Array();
        Array(unsigned int n);
        Array(const Array& src);
        Array& operator=(const Array& src);
        ~Array();

        T& operator[](unsigned int i) const;
        unsigned int size() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& array);

#include "Array.tpp"

#endif
