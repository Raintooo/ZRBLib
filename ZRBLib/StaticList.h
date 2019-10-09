#ifndef STATICLIST_H
#define STATICLIST_H

#include "Seqlist.h"

namespace ZRBLib
{

template <typename T, int N>
class StaticList : public SeqList<T>
{
protected:
    T m_space[N];
public:
    StaticList();
    int capacity() const;
};

template <typename T, int N>
StaticList<T,N>::StaticList()
{
    this->m_array = m_space;
    this->m_length = 0;
}

template <typename T, int N>
int StaticList<T,N>::capacity() const
{
    return N;
}

}


#endif // STATICLIST_H
