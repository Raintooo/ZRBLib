#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

namespace ZRBLib
{

template<typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL);
    SmartPointer(const SmartPointer<T>& obj);
    SmartPointer& operator = (const SmartPointer<T>& obj);
    virtual ~SmartPointer();
};

template<typename T>
SmartPointer<T>::SmartPointer(T* p) : Pointer<T>(p)
{
}

template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& obj)
{
    this->m_pointer = obj.m_pointer;
    const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
}

template<typename T>
SmartPointer<T>& SmartPointer<T>::operator = (const SmartPointer<T>& obj)
{
    if(this->m_pointer != obj.m_pointer)
    {
        T* tmp = this->m_pointer;
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;

        delete tmp;
    }

    return *this;
}

template<typename T>
SmartPointer<T>::~SmartPointer()
{
    delete this->m_pointer;
}


}


#endif // SMARTPOINTER_H
