#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "linklist.h"

namespace ZRBLib
{

template <typename T>
class GTreeNode : public TreeNode<T>
{
    bool m_flag;
protected:
    void* operator new(unsigned int size) throw()
    {
        return Object::operator new(size);
    }
public:
    LinkList<GTreeNode<T>*> child;

    GTreeNode()
    {
        m_flag = false;
    }

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if(ret != NULL)
            ret->m_flag = true;

        return ret;
    }

    bool flag()
    {
        return m_flag;
    }
};

}

#endif // GTREENODE_H
