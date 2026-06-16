#include "CustomVector.h"

template<class T>
CustomVector<T>::CustomVector(){
    this->data = new T[1];
    size = 0;
};

template<class T>
T& CustomVector<T>::operator[](size_t location){
    return (this->data)[location];
};

template<class T>
void CustomVector<T>::push_it(T val){
    if(size == 0){
        ++size;
        this->data[0] = val;
    }
    else
    {
         ++size;
         T *temp = new T[size];
         for(int i = 0; i != (size-1); ++i)
         {
              temp[i] = this->data[i];
         }
         delete[] this->data;
         this->data = temp;
         this->data[size-1]=val;
    }
};