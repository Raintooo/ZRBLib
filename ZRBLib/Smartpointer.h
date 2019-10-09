#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Object.h"

namespace ZRBLib
{

template<typename T>
class SmartPointer : public Object
{
protected:
    T* mp;
public:
    SmartPointer(T* p = NULL);
    SmartPointer(const SmartPointer<T>& obj);
    SmartPointer& operator = (const SmartPointer<T>& obj);
    T* operator -> ();
    T& operator * ();
    T* get();
    bool isNULL();
    virtual ~SmartPointer();
};

template<typename T>
SmartPointer<T>::SmartPointer(T* p)
{
    mp = p;
}

template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& obj)
{
    mp = obj.mp;
    const_cast<SmartPointer<T>&>(obj).mp = NULL;
}

template<typename T>
SmartPointer<T>& SmartPointer<T>::operator = (const SmartPointer<T>& obj)
{
    if(mp != obj.mp)
    {
        delete mp;
        mp = obj.mp;
        const_cast<SmartPointer<T>&>(obj).mp = NULL;
    }

    return *this;
}

template<typename T>
T* SmartPointer<T>::operator -> ()
{
    return mp;
}

template<typename T>
T& SmartPointer<T>::operator * ()
{
    return *mp;
}

template<typename T>
T* SmartPointer<T>::get()
{
    return mp;
}

template<typename T>
bool SmartPointer<T>::isNULL()
{
    return (mp == NULL);
}

template<typename T>
SmartPointer<T>::~SmartPointer()
{
    delete mp;
}


}


#endif // SMARTPOINTER_H
