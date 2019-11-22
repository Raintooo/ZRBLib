#ifndef GTREENODE_H
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
};

}

#endif // GTREENODE_H
