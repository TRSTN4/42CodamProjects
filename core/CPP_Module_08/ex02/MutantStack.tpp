template<typename T, class Container>
MutantStack<T, Container>::MutantStack() {}

template<typename T, class Container>
MutantStack<T, Container>::MutantStack(const MutantStack<T, Container>& src) : std::stack<T, Container>(src) {
    *this = src;
}

template<typename T, class Container>
MutantStack<T, Container>& MutantStack<T, Container>::operator=(const MutantStack<T, Container>& src) {
    if (this != &src)
        std::stack<T, Container>::operator=(src);
    return *this;
}

template<typename T, class Container>
MutantStack<T, Container>::~MutantStack() {}

template<typename T, class Container>
typename Container::iterator MutantStack<T, Container>::begin() {
    return this->c.begin();
}

template<typename T, class Container>
typename Container::iterator MutantStack<T, Container>::end() {
    return this->c.end();
}
