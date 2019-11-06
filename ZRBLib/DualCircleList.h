#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "DualLinkList.h"
#include "LinuxList.h"

namespace ZRBLib
{
template <typename T>
class DualCircleList : public DualLinkList<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head m_header;
    list_head* m_current;

    list_head* position(int index) const;
    int mod(int index) const;

public:
    DualCircleList();
    bool insert(const T& e);
    bool insert(int index, const T& e);
    bool remove(int index);
    bool set(int index, const T& e);
    bool get(int index, T& e) const;
    int find(const T& e) const;
    T get(int index) const;
    int length();
    void clear();

    //链表遍历相关
    bool move(int index, int step = 1);     //step参数用于表示每次移动多少个元素
    T current();
    bool end();
    bool next();
    bool pre();

    ~DualCircleList();
};

template <typename T>
list_head* DualCircleList<T>::position(int index) const
{
    list_head* ret = const_cast<list_head*>(&m_header);

    for(int pos=0; pos<index; ++pos)
    {
        ret = ret->next;
    }

    return ret;
}

template <typename T>
int DualCircleList<T>::mod(int index) const
{
     return (this->m_length == 0) ? 0 : (index % this->m_length);
}

template <typename T>
DualCircleList<T>::DualCircleList()
{
    m_current = NULL;
    this->m_length = 0;
    this->m_step = 1;

    INIT_LIST_HEAD(&m_header);  //  初始化头结点
}

template <typename T>
bool DualCircleList<T>::insert(const T& e)
{
    return insert(this->m_length, e);
}

template <typename T>
bool DualCircleList<T>::insert(int index, const T& e)
{
    bool ret = true;

    index = index % (this->m_length + 1);

    Node* node = new Node();
    if(node != NULL)
    {
        node->value = e;

        list_add_tail(&(node->head), position(index)->next);
        this->m_length++;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough Memory ..");
    }

    return ret;
}


template <typename T>
bool DualCircleList<T>:: remove(int index)
{
    bool ret = (index >= 0) && (index <= this->m_length);

    index = mod(index);

    if(ret)
    {
        list_head* toDel = position(index)->next;

        if(m_current == toDel)
            m_current = toDel->next;

        list_del(toDel);
        this->m_length--;


        delete list_entry(toDel, Node, head);
    }

    return ret;
}

template <typename T>
bool DualCircleList<T>:: set(int index, const T& e)
{
    bool bRet = (index >= 0) && (index < this->m_length);
    index = mod(index);
    if(bRet)
    {
        list_head* cur = position(index)->next;

        list_entry(cur, Node, head)->value = e;
    }

    return bRet;
}

template <typename T>
bool DualCircleList<T>:: get(int index, T& e) const
{
    bool bRet = (index >= 0) && (index < this->m_length);
    index = mod(index);
    if(bRet)
    {
        list_head* cur = position(index)->next;

        e = list_entry(cur, Node, head)->value;
    }

    return bRet;
}

template <typename T>
T DualCircleList<T>::get(int index) const
{
    T tRet;
    if(get(mod(index), tRet))
    {
        return tRet;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Index is invaild...");
    }

    return tRet;
}

template <typename T>
int DualCircleList<T>::find(const T& e) const
{
    int ret = -1;
    int i = 0;
    list_head* slider = NULL;

    list_for_each(slider, &m_header)
    {
        if(list_entry(slider, Node, head)->value == e)
        {
            ret = i;
            break;
        }
        i++;
    }

    return ret;
}

template <typename T>
int  DualCircleList<T>::length()
{
    return this->m_length;
}

template <typename T>
void DualCircleList<T>::clear()
{
    while(this->m_length > 0)
    {
        remove(0);
    }
}

template <typename T>
bool DualCircleList<T>::move(int index, int step)
{
    bool bRet = (index >= 0) && (index < this->m_length) && (step > 0);
    index = mod(index);

    if(bRet)
    {
        m_current = position(index)->next;
        this->m_step = step;
    }

    return bRet;
}

template <typename T>
T DualCircleList<T>::current()
{
    if(!end())
    {
        return list_entry(m_current, Node, head)->value;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, " no value at current position");
    }
}

template <typename T>
bool DualCircleList<T>::end()
{
    return (m_current == NULL) || (this->m_length == 0);
}

template <typename T>
bool DualCircleList<T>::next()
{
    int i = 0;

    while((i < this->m_step) && !end())
    {
        if(m_current != &m_header)
        {
            m_current = m_current->next;
            i++;
        }
        else
        {
            m_current = m_current->next;
        }
    }

    if(m_current == &m_header)
        m_current = m_current->next;

    return (i == this->m_step);
}

template <typename T>
bool DualCircleList<T>::pre()
{
    int i = 0;

    while((i < this->m_step) && !end())
    {
        if(m_current != &m_header)
        {
            m_current = m_current->prev;
            i++;
        }
        else
        {
            m_current = m_current->prev;
        }
    }

    if(m_current == &m_header)
        m_current = m_current->prev;

    return (i == this->m_step);
}

template <typename T>
DualCircleList<T>::~DualCircleList()
{
    clear();
}

}

#endif // DUALCIRCLELIST_H
