#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <iostream>
#include <algorithm>
#include <list>
#include <stack>
#include <deque>

template<typename T, class Container = std::deque<T>>
class MutantStack : public std::stack<T, Container> {
public:
    MutantStack();
    MutantStack(const MutantStack<T, Container>& src);
    MutantStack<T, Container>& operator=(const MutantStack<T, Container>& src);
    ~MutantStack();

    typedef typename Container::iterator iterator;

    iterator begin();
    iterator end();
};

#include "MutantStack.tpp"
#endif
