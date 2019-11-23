#ifndef SINGLETON_H
#define SINGLETON_H

#include "Object.h"

namespace ZRBLib
{
template <typename T>
class SingleTon : public Object
{
    static T* c_instance;

    SingleTon();
    SingleTon(const SingleTon<T>& e);
    SingleTon<T>& operator = (const SingleTon<T>& e);
public:
    static T* NewInstance()
    {
        if(c_instance == NULL)
            c_instance = new T();

        return c_instance;
    }

};

template <typename T>
T* SingleTon<T>::c_instance = NULL;


}

#endif // SINGLETON_H
