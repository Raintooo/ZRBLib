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

    virtual T* array()
    {
        return m_array;
    }
};

template <typename T>
bool Array<T>::set(int index, const T& e)
{
    bool bRet = (index >= 0) && (index < length());
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
T Array<T>::operator [](int index) const    //const 返回对象值 一般用于右值 值是一般不能变
{
    return const_cast<Array<T>&>(*this)[index];     //const成员函数中只能调用const成员函数 所以把const属性除去调用非
                                                    //const版本 重载函数
}

}

#endif // ARRAY_H
