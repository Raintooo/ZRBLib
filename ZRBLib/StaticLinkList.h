#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "linklist.h"

namespace ZRBLib
{

template <typename T, int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;
    struct SNode : public Node
    {
        void* operator new(unsigned int size, void* loc)
        {
            (void)size;     //为了消除警告
            return loc;
        }
    };
    unsigned char m_space[sizeof(SNode)*N];
    int m_used[N];
    Node* create();
    void destory(Node* p);
public:
    StaticLinkList();
    ~StaticLinkList();
};

template <typename T, int N>
StaticLinkList<T,N>::StaticLinkList()
{
    for(int i = 0; i < N; i++)
    {
        m_used[i] = 0;
    }
}

template <typename T, int N>
typename LinkList<T>::Node* StaticLinkList<T,N>::create()
{
    SNode* ret = NULL;
    for(int i = 0; i < N; i++)
    {
        if(!m_used[i])
        {
            ret = reinterpret_cast<SNode*>(m_space) + i;
            ret = new(ret) SNode();     //在指定地址申请空间
            m_used[i] = 1;
            break;
        }
    }

    return ret;
}

template <typename T, int N>
void StaticLinkList<T,N>::destory(Node* p)
{
    SNode* space = reinterpret_cast<SNode*>(m_space);
    SNode* ptmp = dynamic_cast<SNode*>(p);
    for(int i = 0; i < N; i++)
    {
        if(p == (space + i))
        {
            m_used[i] = 0;
            ptmp->~SNode();
            break;
        }
    }
}

template <typename T, int N>
StaticLinkList<T,N>::~StaticLinkList()
{
    this->clear();
}

}


#endif // STATICLINKLIST_H
