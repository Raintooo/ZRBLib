#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "Seqlist.h"
#include "Exception.h"

namespace ZRBLib
{

template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;
public:
    DynamicList(int capacity);
    int capacity() const;
    void resize(int capacity);
    ~DynamicList();
};

template <typename T>
DynamicList<T>::DynamicList(int capacity)
{
    this->m_array = new T[capacity];
    if(this->m_array != NULL)
    {
        this->m_capacity = capacity;
        this->m_length = 0;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No Enough Memory..");
    }
}

template <typename T>
void DynamicList<T>::resize(int capacity)
{
    if(capacity != this->m_capacity)
    {
        T* new_array = new T[capacity];
        if(new_array != NULL)
        {
            int len = this->m_length > capacity ? capacity : this->m_length;
            for(int i = 0; i < len; i++)
            {
                new_array[i] = this->m_array[i];
            }

            T* tmp = this->m_array;
            this->m_array = new_array;
            this->m_capacity = capacity;
            this->m_length = len;

            delete[] tmp;

            /*
                这里为什么不是直接delete this->m_array
                是因为如果泛指类型 T 是类类型, delete 会触发相应析构函数,但是析构函数有可能会抛出异常导致函数退出 后面的信息重新赋值就无法执行
                所以就会导致最后 resize后的list的信息不准确而无法使用
                我们要保证函数是异常安全的 所以这里先用临时指针指向原内存地址,m_array指向新空间,最后释放旧空间
            */
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No Enough Memory..");
        }

    }
}

template <typename T>
int DynamicList<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
DynamicList<T>::~DynamicList()
{
    delete[] this->m_array;
}

}


#endif // DYNAMICLIST_H
