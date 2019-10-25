#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"

namespace ZRBLib
{

template <typename T>
class DualLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
        Node* pre;
    };

    /*定义为结构体 是避免泛指类型为类类型时候 不触发构造函数
      继承 Object类避免内存布局与节点结构体不同
    */
    mutable struct : public Object
    {
        char reserved[sizeof(T)];   //内存大小对齐
        Node* next;
        Node* pre;
    } m_header;     //Mutable 可让该成员变量在const 函数可修改


    Node* position(int index) const
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
    DualLinkList();
    bool insert(const T& e);
    bool insert(int index, const T& e);
    bool remove(int index);
    bool set(int index, const T& e);
    bool get(int index, T& e) const;
    int find(const T& e) const;
    virtual T get(int index) const;
    int length();
    void clear();

    //链表遍历相关
    virtual bool move(int index, int step = 1);     //step参数用于表示每次移动多少个元素
    T current();
    virtual bool end();
    virtual bool next();
    virtual bool pre();

    ~DualLinkList();

};

template <typename T>
 DualLinkList<T>::DualLinkList()
{
    m_header.next = NULL;
    m_header.pre = NULL;
    m_length = 0;
    m_step = 1;
    m_current = NULL;
}

template <typename T>
bool  DualLinkList<T>::insert(int index, const T& e)
{
    bool bRet = (index >= 0) && (index <= m_length);
    if(bRet)
    {
        Node* node = create();
        if(node != NULL)
        {
            Node* cur = position(index);
            Node* next = cur->next;

            node->value = e;

            cur->next = node;

            if(cur != reinterpret_cast<Node*>(&m_header))
                node->pre = cur;
            else
                node->pre = NULL;

            if(next != NULL)
            {
                node->next = next;
                next->pre = node;
            }
            else
            {
                node->next = NULL;
            }

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
bool  DualLinkList<T>::insert(const T& e)
{
    return insert(m_length, e);
}

template <typename T>
bool  DualLinkList<T>::remove(int index)
{
    bool bRet = (index >= 0) && (index <= m_length);
    if(bRet)
    {
        Node* cur = position(index);
        Node* toDel = cur->next;
        Node* next = toDel->next;

        if(m_current == toDel)      //todo:这里加个判断是因为假如调用 remove 后再调用 current() 此时 m_current指针指向已经删除的节点，会输出错误数据,
        {
            m_current = toDel->next;
        }

        cur->next = next;    //cur->next->next;

        if(next != NULL)
        {
            next->pre = cur;
        }

        m_length--;
        destory(toDel);
    }
    return bRet;
}

template <typename T>
bool  DualLinkList<T>::set(int index, const T& e)
{
    bool bRet = (index >= 0) && (index < m_length);
    if(bRet)
    {
        Node* cur = position(index);

        cur->next->value = e;
    }

    return bRet;
}

template <typename T>
bool  DualLinkList<T>::get(int index, T& e) const
{
    bool bRet = (index >= 0) && (index < m_length);
    if(bRet)
    {
        Node* cur = position(index);

        e = cur->next->value;
    }

    return bRet;
}

template <typename T>
int  DualLinkList<T>::find(const T& e) const
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
T  DualLinkList<T>::get(int index) const
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
int  DualLinkList<T>::length()
{
    return m_length;
}


template <typename T>
void  DualLinkList<T>::clear()
{
    while(m_length > 1)
        remove(1);
    if(m_length == 1)
    {
        Node* toDel = m_header.next;
        m_header.next = toDel->next;
        m_length--;
        destory(toDel);
    }
}

template <typename T>
bool  DualLinkList<T>::move(int index, int step)
{
    bool ret = (index >= 0) && (index < m_length) && (step > 0);
    if(ret)
    {
        m_current = position(index)->next;
        m_step = step;
    }
    return ret;
}


template <typename T>
bool  DualLinkList<T>::end()
{
    return (m_current == NULL);
}

template <typename T>
bool  DualLinkList<T>::next()
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
bool  DualLinkList<T>::pre()
{
    int i = 0;
    while((i < m_step) && !end())
    {
        m_current = m_current->pre;
        i++;
    }

    return (i == m_step);
}

template <typename T>
T  DualLinkList<T>::current()
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
 DualLinkList<T>::~ DualLinkList()
{
    clear();
}

}

#endif // DUAL DualLinkList_H
