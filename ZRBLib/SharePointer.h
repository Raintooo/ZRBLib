#ifndef SHAREPOINTER_H
#define SHAREPOINTER_H

#include <cstdlib>
#include "Pointer.h"
#include "Exception.h"


namespace ZRBLib
{
template <typename T>
class SharePointer : public Pointer<T>
{
protected:
    int* m_ref;
    void assign(const SharePointer<T>& obj);
public:
    SharePointer(T* p = NULL);
    SharePointer(const SharePointer<T>& obj);
    SharePointer<T>& operator = (const SharePointer<T>& obj);
    void clear();
    ~SharePointer();
};

template <typename T>
SharePointer<T>::SharePointer(T* p) : m_ref(NULL)
{
    if(p)
    {
        this->m_ref = static_cast<int*>(malloc(sizeof(int)));

        if(this->m_ref)
        {
            *(this->m_ref) = 1;
            this->m_pointer = p;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no enough memory");
        }

    }
}
template <typename T>
void SharePointer<T>::assign(const SharePointer<T>& obj)
{
    this->m_ref = obj.m_ref;
    this->m_pointer = obj.m_pointer;

    if(this->m_ref)
    {
        *(this->m_ref) += 1;        //这里 加1 是因为此时触发了拷贝构造函数 说明有新的指针指向该堆空间,计数就加1；
    }
}

template <typename T>
SharePointer<T>::SharePointer(const SharePointer<T>& obj) : Pointer<T>(NULL)
{
    assign(obj);
}

template <typename T>
SharePointer<T>& SharePointer<T>::operator = (const SharePointer<T>& obj)
{
    if(this != &obj)
    {
        clear();        //这里先清除 是因为左值可能是已经指向其他堆空间了 先清除再赋值；
        assign(obj);
    }

    return *this;
}

template <typename T>
void SharePointer<T>::clear()
{
    int* ref = this->m_ref;
    T* toDel = this->m_pointer;

    this->m_pointer = NULL;
    this->m_ref = NULL;

    if(ref)
    {
        (*ref)--;
        if(*ref == 0)    //ref == 0 表明已经没有指针指向堆空间，就释放该堆空间
        {
            free(ref);
            delete toDel;
        }
    }

}

template <typename T>
SharePointer<T>::~SharePointer()
{
    clear();
}

template <typename T>
bool operator == (const SharePointer<T>& l, const SharePointer<T>& r)
{
    return (l.get() == r.get());
}

template <typename T>
bool operator != (const SharePointer<T>& l, const SharePointer<T>& r)
{
    return !(l == r);
}

}

#endif // SHAREPOINTER_H
