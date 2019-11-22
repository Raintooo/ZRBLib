#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace ZRBLib
{
template <typename T>
class TreeNode : public Object
{
public:
    T value;
    TreeNode* parent;
    TreeNode();

    virtual ~TreeNode() = 0;
};

template <typename T>
TreeNode<T>::TreeNode()
{
    parent = NULL;
}

template <typename T>
TreeNode<T>::~TreeNode()
{

}

}



#endif // TREENODE_H
