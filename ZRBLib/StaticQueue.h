#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Exception.h"

namespace ZRBLib
{

template <typename T, int N>
class StaticQueue : public Queue<T>
{
protected:
    T m_space[N];
    int m_front;    //队头
    int m_rear;     //队尾
    int m_length;
public:
    StaticQueue();
    int Capacity() const;
    void add(const T& e);
    void remove() ;
    T front() const;
    void clear() ;
    int length() const ;
};


template <typename T, int N>
StaticQueue<T, N>::StaticQueue()
{
    m_front = 0;
    m_rear = 0;
    m_length = 0;
}

template <typename T, int N>
int StaticQueue<T, N>::Capacity() const
{
    return N;
}

template <typename T, int N>
void StaticQueue<T, N>::add(const T& e)
{
    if(m_length < N)
    {
        m_space[m_rear] = e;
        m_rear = (m_rear + 1) % N;
        m_length++;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "No space in current queue");
    }
}

template <typename T, int N>
void StaticQueue<T, N>::remove()
{
    if(m_length > 0)
    {
        m_front = (m_front + 1) % N;
        m_length--;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "No element in current queue");
    }
}

template <typename T, int N>
T StaticQueue<T, N>::front() const
{
    if(m_length > 0)
    {
        return m_space[m_front];
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "No element in current queue");
    }
}

template <typename T, int N>
void StaticQueue<T, N>::clear()
{
    m_front = 0;
    m_length = 0;
    m_rear = 0;
}

template <typename T, int N>
int StaticQueue<T, N>::length() const
{
    return m_length;
}

}

#endif // STATICQUEUE_H
