#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace ZRBLib
{

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    T* copy(T* array, int currlen,int newlen);
    void update(T* array, int len);
    void init(T* array, int len);
public:
    DynamicArray(int len);
    DynamicArray(const DynamicArray<T>& obj);
    DynamicArray<T>& operator = (const DynamicArray<T>& obj);

    int length() const;
    void resize(int length);
    ~DynamicArray();
};

template <typename T>
T* DynamicArray<T>::copy(T* array, int currlen, int newlen)
{
    T* new_array = new T[newlen];
    if(new_array != NULL)
    {
        int len = currlen > newlen ? newlen : currlen;
        for(int i = 0; i < len; i++)
        {
            new_array[i] = array[i];
        }
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough Memory ..");
    }

    return new_array;
}

template <typename T>
void DynamicArray<T>::update(T* array, int len)
{
    if(array != NULL)
    {
        T* tmp = this->m_array;
        this->m_length = len;
        this->m_array = array;

        delete[] tmp;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough Memory ..");
    }
}

template <typename T>
void DynamicArray<T>::init(T* array, int len)
{
    if(array != NULL)
    {
        this->m_length = len;
        this->m_array = array;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough Memory ..");
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(int len)
{
    init(new T[len], len);
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& obj)
{
    init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator = (const DynamicArray<T>& obj)
{
    if(this != &obj)
    {
        update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }

    return *this;
}

template <typename T>
int DynamicArray<T>::length() const
{
    return m_length;
}

template <typename T>
void DynamicArray<T>::resize(int length)
{
    if(this->m_length != length)
    {
        update(copy(this->m_array, this->m_length, length), length);
    }

}
template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] this->m_array;
}

}


#endif // DYNAMICARRAY_H
