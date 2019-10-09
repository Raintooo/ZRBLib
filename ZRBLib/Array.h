#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"

namespace ZRBLib
{

template <typename T>
class Array : public Object
{
protected:
    T* m_array;
public:
    virtual bool set(int index, const T& e);
    virtual bool get(int index, T& e) const;
    virtual int length() const = 0;

    T& operator [](int inedex);
    T operator [](int index) const;
};

template <typename T>
bool Array<T>::set(int index, const T& e)
{
    bool bRet = (index > 0) && (index < length());
    if(bRet)
    {
        m_array[index] = e;
    }

    return bRet;
}

template <typename T>
bool Array<T>::get(int index, T& e) const
{
    bool bRet = (index > 0) && (index < length());
    if(bRet)
    {
        e = m_array[index];
    }

    return bRet;
}

template <typename T>
T& Array<T>::operator [](int index)
{
    bool bRet = ((0 <= index) && (index < length()));
    if(bRet)
        return m_array[index];
    else
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter is invaild.");
}

template <typename T>
T Array<T>::operator [](int index) const
{
    return const_cast<Array<T>&>(*this)[index];
}

}

#endif // ARRAY_H
