#pragma once

#include <stdio.h>

template<class T> class CustomVector{
public:
    CustomVector();
    void push_it(T val);
    T& operator[](size_t);
private:
    T *data;
    size_t size;
};