template <typename T>
Array<T>::Array(): array(nullptr), length(0) {}

template <typename T>
Array<T>::Array(unsigned int n): array(new T[n]()), length(n) {}

template <typename T>
Array<T>::Array(const Array& src): array(new T[src.length]()), length(src.length) {
    for (unsigned int i = 0; i < length; i++)
        array[i] = src.array[i];
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& src) {
    if (this != &src) {
        delete[] array;
        array = new T[src.length]();
        length = src.length;
        for (unsigned int i = 0; i < length; i++)
            array[i] = src.array[i];
    }
    return *this;
}

template <typename T>
Array<T>::~Array() {
    delete[] array;
}

template <typename T>
unsigned int Array<T>::size() const {
    return length;
}

template <typename T>
T& Array<T>::operator[](unsigned int i) const {
    if (i >= length)
        throw std::out_of_range("Index out of range");
    return array[i];
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& array) {
    for (unsigned int i = 0; i < array.size(); i++)
        out << array[i] << " ";
    return out;
}
