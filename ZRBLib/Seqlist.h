#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace ZRBLib
{

template <typename T>
class SeqList : public List<T>
{
protected:
    T* m_array;
    int m_length;
public:
    bool insert(int index, const T& e);
    bool remove(int index);
    bool set(int index, const T& e);
    bool get(int index, T& e) const;
    int length();
    void clear();

    T& operator [] (int index);
    T operator [] (int index) const;

    virtual int capacity() const = 0;
};

template <typename T>
bool SeqList<T>::insert(int index, const T& e)
{
    bool bRet = ((0 <= index) && (index <= m_length));
    bRet = bRet && ((m_length + 1) <= 10);

    if(bRet)
    {
        for(int j = m_length - 1; j >= index; j--)
        {
            m_array[j+1] = m_array[j];
        }
        m_array[index] = e;
        m_length++;
    }
    return bRet;
}

template <typename T>
bool SeqList<T>::remove(int index)
{
    bool bRet = ((0 <= index) && (index < m_length));

    if(bRet)
    {
        for(int j = index; j < m_length; j++)
        {
            m_array[j] = m_array[j+1];
        }
        m_length--;
    }

    return bRet;
}

template <typename T>
bool SeqList<T>::set(int index, const T& e)
{
    bool bRet = ((0 <= index) && (index < m_length));

    if(bRet)
    {
        m_array[index] = e;
    }
    return bRet;
}

template <typename T>
bool SeqList<T>::get(int index, T& e) const
{
    bool bRet = ((0 <= index) && (index < m_length));

    if(bRet)
    {
        e = m_array[index];
    }
    return bRet;
}

template <typename T>
int SeqList<T>::length()
{
    return m_length;
}

template <typename T>
void SeqList<T>::clear()
{
    m_length = 0;   //  m_length = 0 前面的插入删除设置操作前的判断就为假,认为是清空了
}

template <typename T>
T& SeqList<T>::operator [](int index)
{
    bool bRet = ((0 <= index) && (index < m_length));
    if(bRet)
        return m_array[index];
    else
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter is invaild.");

}

template <typename T>
T SeqList<T>::operator [](int index) const
{
    return (const_cast<SeqList<T>&>(*this))[index]; //const 成员函数不能调用非const成员函数所以将this指针的const去掉就可以调用非const
}

}

#endif // SEQLIST_H
