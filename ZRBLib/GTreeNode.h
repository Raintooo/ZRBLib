﻿#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "linklist.h"

namespace ZRBLib
{

template <typename T>
class GTreeNode : public TreeNode<T>
{
public:
    LinkList<GTreeNode<T>*> child;

    GTreeNode()
    {
    }

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if(ret != NULL)
            ret->m_flag = true;

        return ret;
    }
};

}

#endif // GTREENODE_H
