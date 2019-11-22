#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception.h"

namespace ZRBLib
{
template <typename T>
class GTree : public Tree<T>
{
protected:
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const;
    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const;
public:
    bool insert(TreeNode<T>* node);
    bool insert(const T& value, TreeNode<T>* parent);
    SharePointer< Tree<T> > remove(const T& value);
    SharePointer< Tree<T> > remove(TreeNode<T>* node);
    GTreeNode<T>* find(const T& value) const;
    GTreeNode<T>* find(TreeNode<T>* node) const;
    GTreeNode<T>* root() const;
    int degree();
    int count();
    int height();
    void clear();
};

template <typename T>
bool GTree<T>::insert(TreeNode<T>* node)
{
    bool ret;

    if(node != NULL)
    {
        if(this->m_root == NULL)
        {
            node->parent = NULL;
            this->m_root = node;
            this->m_root->value = node->value;
        }
        else
        {
            GTreeNode<T>* np = find(node->parent);
            if(np != NULL)
            {
                GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);
                if(np->child.find(n) < 0)
                {
                    ret = np->child.insert(n);
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "Invaild parent tree node...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Paramter node can not be NULL...");
    }

    return ret;
}

template <typename T>
bool GTree<T>::insert(const T& value, TreeNode<T>* parent)
{
    bool ret;

    GTreeNode<T>* node = new GTreeNode<T>();
    if(node != NULL)
    {
        node->value = value;
        node->parent = parent;

        insert(node);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No Enough Memory...");
    }

    return ret;
}

template <typename T>
SharePointer< Tree<T> > GTree<T>::remove(const T& value)
{
    return NULL;
}

template <typename T>
SharePointer< Tree<T> > GTree<T>::remove(TreeNode<T>* node)
{
    return NULL;
}

template <typename T>
GTreeNode<T>* GTree<T>::find(GTreeNode<T>* node, GTreeNode<T>* obj) const
{
    GTreeNode<T>* ret = NULL;

    if(node == obj)
    {
        return node;
    }
    else
    {
        if(node != NULL)
        {
            for(node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
            {
                ret = find(node->child.current(), obj);
            }
        }
    }

    return ret;
}

template <typename T>
GTreeNode<T>* GTree<T>::find(GTreeNode<T>* node, const T& value) const
{
    GTreeNode<T>* ret = NULL;

    if(node != NULL)
    {
        if(node->value == value)
        {
            return node;
        }
        else
        {
            for(node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
            {
                ret = find(node->child.current(), value);
            }
        }
    }

    return ret;
}

template <typename T>
GTreeNode<T>* GTree<T>::find(const T& value) const
{
    return find(root(), value);
}

template <typename T>
GTreeNode<T>* GTree<T>::find(TreeNode<T>* node) const
{
    return find(root(), dynamic_cast<GTreeNode<T>*>(node));
}

template <typename T>
GTreeNode<T>* GTree<T>::root() const
{
    return NULL;
}

template <typename T>
int GTree<T>::degree()
{
    return 0;
}

template <typename T>
int GTree<T>::count()
{
    return 0;
}

template <typename T>
int GTree<T>::height()
{
    return 0;
}

template <typename T>
void GTree<T>::clear()
{
    return ;
}


}

#endif // GTREE_H
