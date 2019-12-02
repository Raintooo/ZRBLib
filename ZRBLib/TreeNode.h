#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace ZRBLib
{
template <typename T>
class TreeNode : public Object
{
protected:
    bool m_flag;
    TreeNode(const TreeNode<T>& e);
    TreeNode<T>& operator = (const TreeNode<T>& e);
    void* operator new(unsigned int size) throw()
    {
        return Object::operator new(size);
    }
public:
    T value;
    TreeNode* parent;
    TreeNode();

    virtual ~TreeNode() = 0;

    bool flag()
    {
        return m_flag;
    }
};

template <typename T>
TreeNode<T>::TreeNode()
{
    m_flag = false;
    parent = NULL;
}

template <typename T>
TreeNode<T>::~TreeNode()
{

}

}



#endif // TREENODE_H
