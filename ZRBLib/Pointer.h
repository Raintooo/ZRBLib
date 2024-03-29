﻿#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

namespace ZRBLib
{
template <typename T>
class Pointer : public Object
{
protected:
    T* m_pointer;
public:
    Pointer(T* p = NULL);
    T* operator ->();
    T& operator *();
    const T* operator ->() const;
    const T& operator *() const;
    bool isNull() const;
    T* get() const;
};

template <typename T>
Pointer<T>::Pointer(T* p)
{
    m_pointer = p;
}

template <typename T>
T* Pointer<T>::operator ->()
{
    return m_pointer;
}

template <typename T>
T& Pointer<T>::operator *()
{
    return *m_pointer;
}

template <typename T>
const T* Pointer<T>::operator ->() const
{
    return m_pointer;
}

template <typename T>
const T& Pointer<T>::operator *() const
{
    return *m_pointer;
}

template <typename T>
bool Pointer<T>::isNull() const
{
    return (m_pointer == NULL);
}

template <typename T>
T* Pointer<T>::get() const
{
    return m_pointer;
}


}

#endif // POINTER_H
