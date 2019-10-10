#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace ZRBLib
{

template <typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    /*定义为结构体 是避免泛指类型为类类型时候 不触发构造函数
      继承 Object类避免内存布局与节点结构体不同
    */
    mutable struct : public Object
    {
        char reserved[sizeof(T)];   //内存大小对齐
        Node* next;
    } m_header;     //Mutable 可让该成员变量在const 函数可修改


    Node* SearchNode(int index) const
    {
        Node* cur = reinterpret_cast<Node*>(&m_header);
        for(int i = 0; i < index; i++)
        {
            cur = cur->next;
        }

        return cur;
    }

    virtual Node* create()
    {
        return new Node();
    }
    virtual void destory(Node* p)
    {
        delete p;
    }

    int m_length;
    int m_step;
    Node* m_current;

public:
    LinkList();
    bool insert(const T& e);
    bool insert(int index, const T& e);
    bool remove(int index);
    bool set(int index, const T& e);
    bool get(int index, T& e) const;
    int find(const T& e) const;
    T get(int index);
    int length();
    void clear();

    //链表遍历相关
    bool move(int index, int step = 1);     //step参数用于表示每次移动多少个元素
    T current();
    bool end();
    bool next();

    ~LinkList();

};

template <typename T>
LinkList<T>::LinkList()
{
    m_header.next = NULL;
    m_length = 0;
    m_step = 1;
    m_current = NULL;
}

template <typename T>
bool LinkList<T>::insert(int index, const T& e)
{
    bool bRet = (index >= 0) && (index <= m_length);
    if(bRet)
    {
        Node* node = create();
        if(node != NULL)
        {
            Node* cur = SearchNode(index);

            node->value = e;
            node->next = cur->next;
            cur->next = node;

            m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough Memory ..");
        }
    }

    return bRet;
}

template <typename T>
bool LinkList<T>::insert(const T& e)
{
    return insert(m_length, e);
}

template <typename T>
bool LinkList<T>::remove(int index)
{
    bool bRet = (index >= 0) && (index <= m_length);
    if(bRet)
    {
        Node* cur = SearchNode(index);

        Node* toDel = cur->next;
        cur->next = toDel->next;    //cur->next->next;

        m_length--;
        destory(toDel);
    }
    return bRet;
}

template <typename T>
bool LinkList<T>::set(int index, const T& e)
{
    bool bRet = (index >= 0) && (index < m_length);
    if(bRet)
    {
        Node* cur = SearchNode(index);

        cur->next->value = e;
    }

    return bRet;
}

template <typename T>
bool LinkList<T>::get(int index, T& e) const
{
    bool bRet = (index >= 0) && (index < m_length);
    if(bRet)
    {
        Node* cur = SearchNode(index);

        e = cur->next->value;
    }

    return bRet;
}

template <typename T>
int LinkList<T>::find(const T& e) const
{
    int index = 0;
    int ret = -1;
    Node* node = m_header.next;
    while(node != NULL)
    {
        if(node->value == e)
        {
            ret = index;
            break;
        }
        index++;
        node = node->next;
    }

    return ret;
}

template <typename T>
T LinkList<T>::get(int index)
{
    T tRet;
    if(get(index, tRet))
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
int LinkList<T>::length()
{
    return m_length;
}


template <typename T>
void LinkList<T>::clear()
{
    while(m_header.next != NULL)
    {
        Node* toDel = m_header.next;
        m_header.next = toDel->next;
       // m_length--;
       destory(toDel);
    }
    m_length = 0;
}

template <typename T>
bool LinkList<T>::move(int index, int step)
{
    bool ret = (index >= 0) && (index < m_length) && (step > 0);
    if(ret)
    {
        m_current = SearchNode(index)->next;
        m_step = step;
    }
    return ret;
}


template <typename T>
bool LinkList<T>::end()
{
    return (m_current == NULL);
}

template <typename T>
bool LinkList<T>::next()
{
    int i = 0;
    while((i < m_step) && !end())
    {
        m_current = m_current->next;
        i++;
    }

    return (i == m_step);
}

template <typename T>
T LinkList<T>::current()
{
    if(m_current != NULL)
    {
        return m_current->value;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, " no value at current position");
    }
}

template <typename T>
LinkList<T>::~LinkList()
{
    clear();
}

}


#endif // LINKLIST_H
