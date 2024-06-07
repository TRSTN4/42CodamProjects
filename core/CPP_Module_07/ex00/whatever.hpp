#ifndef ITER_H
#define ITER_H

#include <iostream>

template<typename Template>
Template max(Template& a, Template& b) {
    if (a > b)
        return a;
    else
        return b;
}

template<typename Template>
Template min(Template& a, Template& b) {
    if (a < b)
        return a;
    else
        return b;
}

template<typename Template>
void swap(Template& value1, Template& value2) {
    Template temp = value1;
    value1 = value2;
    value2 = temp;
}

#endif
