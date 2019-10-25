#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "linklist.h"

namespace ZRBLib
{

template <typename T>
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;
    Node* last();           //O(n)
    void last_to_first();   //O(n)
    int mode(int i) const;  //O(1)
public:
    bool insert(const T& e);            //O(n)
    bool insert(int index, const T& e); //O(n)
    bool remove(int index);             //O(n)
    bool set(int index, const T& e);    //O(1)
    bool get(int index, T& e) const;    //O(n)
    int find(const T& e) const;         //O(n)
    T get(int index) const;             //O(n)
    void clear();                       //O(n)
    bool move(int index, int step = 1); //O(n)
    bool end();                         //O(1)

    ~CircleList();                      //O(n)
};

template <typename T>
typename LinkList<T>::Node* CircleList<T>::last()
{
    return LinkList<T>::position(this->m_length - 1)->next;
}

template <typename T>
void CircleList<T>::last_to_first()
{
    last()->next = this->m_header.next;
}

template <typename T>
int CircleList<T>::mode(int i) const
{
    return (this->m_length == 0 ? 0 : (i % this->m_length));
}

template <typename T>
bool CircleList<T>::insert(const T& e)
{
    return insert(this->m_length, e);
}

template <typename T>
bool CircleList<T>::insert(int index, const T& e)
{
    bool ret = false;

    index = index % (this->m_length + 1);
    ret = LinkList<T>::insert(index, e);

    if(ret && (index == 0))
    {
        last_to_first();
        /*
            这里index == 0 即首节点时候就将next指针指回首节点, 那么后面的节点加入到首节点时候,
            加入的节点会继承 首节点的next指针指向的地方(首节点的next指针指回了首节点本身)
            所以后面的节点插入后尾指针自动指回首节点
        */
    }

    return ret;
}

template <typename T>
bool CircleList<T>::remove(int index)
{
    bool ret = false;

    index = mode(index);

    if(index == 0)
    {

        Node* toDel = this->m_header.next;

        if(toDel != NULL)
        {
            this->m_header.next = toDel->next;
            this->m_length--;

            if(this->m_length > 0)
            {
                last_to_first();

                if(this->m_current == toDel)
                    this->m_current = toDel->next;

            }
            else
            {
                this->m_header.next = NULL;
                this->m_current = NULL;
            }
            ret = true;
            this->destory(toDel);
        }
        else
        {
            ret = false;
        }
    }
    else
    {
        ret = LinkList<T>::remove(index);
    }

    return ret;
}

template <typename T>
bool CircleList<T>::set(int index, const T& e)
{
    return LinkList<T>::set(mode(index), e);
}

template <typename T>
bool CircleList<T>::get(int index, T& e) const
{
    return LinkList<T>::get(mode(index), e);
}

template <typename T>
T CircleList<T>:: get(int index) const
{
    return LinkList<T>::get(mode(index));
}

template <typename T>
int CircleList<T>::find(const T& e) const
{
    int ret = -1;
    Node* node = this->m_header.next;

    for(int i = 0; i < this->m_length; i++)
    {
        if(node->value == e)
        {
            ret = i;
            break;
        }
        node = node->next;
    }

    return ret;
}

template <typename T>
void CircleList<T>::clear()
{
    while(this->m_length > 1)
        remove(1);              //这里remove(1) 不是 remove(0) 是因为 移除 0位置时 会调用 last_to_first => last()进行很多调用, 效率不高

    if(this->m_length == 1)
    {
        Node* toDel = this->m_header.next;
        this->m_header.next = NULL;
        this->m_length = 0;
        this->m_current = NULL;

        this->destory(toDel);
    }
}

template <typename T>
bool CircleList<T>::move(int index, int step)
{
    return LinkList<T>::move(mode(index), step);
}

template <typename T>
bool CircleList<T>::end()
{
    return (this->m_length == 0 || this->m_current == NULL);
}

template <typename T>
CircleList<T>::~CircleList()
{
    clear();
}

}



#endif // CIRCLELIST_H
