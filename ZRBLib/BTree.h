#ifndef BTREE_H
#define BTREE_H

#include "BTreeNode.h"
#include "Tree.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace ZRBLib
{

enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT,
};

template <typename T>
class BTree : public Tree<T>
{
protected:
    virtual BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const;
    virtual BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const;
    virtual bool insert(BTreeNode<T>* node, BTreeNode<T>* np, BTNodePos type) const;
    virtual void remove(BTreeNode<T>* node, BTree<T>*& ret);
    virtual void free(BTreeNode<T>* node);
    virtual int count(BTreeNode<T>* node) const;
    virtual int height(BTreeNode<T>* node) const;
    virtual int degree(BTreeNode<T>* node) const;
public:
    bool insert(TreeNode<T>* node);
    bool insert(TreeNode<T>* node, BTNodePos pos);
    bool insert(const T& value, TreeNode<T>* parent);
    bool insert(const T& value, TreeNode<T>* parent, BTNodePos pos);
    SharePointer< Tree<T> > remove(const T& value);
    SharePointer< Tree<T> > remove(TreeNode<T>* node);
    BTreeNode<T>* find(const T& value) const;
    BTreeNode<T>* find(TreeNode<T>* node) const;
    BTreeNode<T>* root() const;
    int degree() const;
    int count() const;
    int height() const;
    void clear();
};


template <typename T>
bool BTree<T>::insert(BTreeNode<T>* node, BTreeNode<T>* np, BTNodePos type) const
{
    bool ret = true;

    if(type == ANY)
    {
        if(np->left == NULL)
            np->left = node;
        else if(np->right == NULL)
            np->right = node;
        else
            ret = false;
    }
    else if(type == LEFT)
    {
        if(np->left == NULL)
            np->left = node;
        else
            ret = false;
    }
    else if(type == RIGHT)
    {
        if(np->right == NULL)
            np->right = node;
        else
            ret = false;
    }
    else
    {
        ret = false;
    }

    return ret;
}

template <typename T>
bool BTree<T>::insert(TreeNode<T>* node, BTNodePos pos)
{
    bool ret = false;

    if(node != NULL)
    {
        if(this->m_root == NULL)
        {
            this->m_root = node;
            node->parent = NULL;
        }
        else
        {
            BTreeNode<T>* np = find(node->parent);
            if(np != NULL)
                ret = insert(dynamic_cast<BTreeNode<T>*>(node), np, pos);
            else
                THROW_EXCEPTION(InvalidParameterException, "invaild parent tree");
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Paramter can not be NULL");
    }


    return ret;
}

template <typename T>
bool BTree<T>::insert(const T& value, TreeNode<T>* parent, BTNodePos pos)
{
    bool ret = false;

    BTreeNode<T>* node = BTreeNode<T>::NewNode();
    if(node != NULL)
    {
        node->value = value;
        node->parent = parent;

        ret = insert(node, pos);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create BtreeNode..");
    }

    return ret;
}

template <typename T>
bool BTree<T>::insert(TreeNode<T>* node)
{
    return insert(node, ANY);
}

template <typename T>
bool BTree<T>::insert(const T& value, TreeNode<T>* parent)
{
    return insert(value, parent, ANY);
}

template <typename T>
void BTree<T>::remove(BTreeNode<T>* node, BTree<T>*& ret)
{
    ret = new BTree<T>();

    if(ret != NULL)
    {
        if(this->m_root != node)
        {
            BTreeNode<T>* np = dynamic_cast<BTreeNode<T>*>(node->parent);

            if(np != NULL)
            {
                if(np->left == node)
                    np->left = NULL;
                if(np->right == node)
                    np->right = NULL;

                node->parent = NULL;
            }
        }
        else
        {
            this->m_root = NULL;
        }
        ret->m_root = node;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create Btree..");
    }
}

template <typename T>
SharePointer< Tree<T> > BTree<T>::remove(const T& value)
{
    BTree<T>* ret;
    BTreeNode<T>* node = find(value);

    if(node != NULL)
        remove(node, ret);
    else
        THROW_EXCEPTION(InvalidParameterException, "Paramter is invaild");

    return ret;
}

template <typename T>
SharePointer< Tree<T> > BTree<T>::remove(TreeNode<T>* node)
{
    BTree<T>* ret;

    node = find(node);

    if(node != NULL)
        remove(dynamic_cast<BTreeNode<T>*>(node), ret);
    else
        THROW_EXCEPTION(InvalidParameterException, "Paramter is invaild");

    return ret;
}

template <typename T>
BTreeNode<T>* BTree<T>::find(BTreeNode<T>* node, const T& value) const
{
    BTreeNode<T>* ret = NULL;
    if(node != NULL)
    {
        if(node->value == value)
        {
            ret = node;
        }
        else
        {
            if(ret == NULL)
                ret = find(node->left, value);

            if(ret == NULL)
                ret = find(node->right, value);
        }
    }

    return ret;
}

template <typename T>
BTreeNode<T>* BTree<T>::find(BTreeNode<T>* node, BTreeNode<T>* obj) const
{
    BTreeNode<T>* ret = NULL;

    if(node != NULL)
    {
        if(node == obj)
        {
            ret = obj;
        }
        else
        {
            if(ret == NULL)
                ret = find(node->left, obj);
            if(ret == NULL)
                ret = find(node->right, obj);
        }
    }

    return ret;
}

template <typename T>
BTreeNode<T>* BTree<T>::find(const T& value) const
{
    return find(root(), value);
}

template <typename T>
BTreeNode<T>* BTree<T>::find(TreeNode<T>* node) const
{
    return find(root(), dynamic_cast<BTreeNode<T>*>(node));
}

template <typename T>
BTreeNode<T>* BTree<T>::root() const
{
    return dynamic_cast<BTreeNode<T>*>(this->m_root);
}

template <typename T>
int BTree<T>::degree(BTreeNode<T>* node) const
{
    int ret = 0;

    if(node != NULL)
    {
        BTreeNode<T>* child[] = {node->left, node->right};

        ret = (!!node->left) + (!!node->right);     //两次取反将地址值转换为0或1

        for(int i = 0; (i < 2)&&(ret < 2); i++)
        {
            int d = degree(child[i]);

            if(d > ret)
                ret = d;
        }
    }
    return ret;
}

template <typename T>
int BTree<T>::degree() const
{
    return degree(root());
}

template <typename T>
int BTree<T>::count(BTreeNode<T>* node) const
{
    int ret = 0;

    if(node != NULL)
    {
        ret = 1;
        ret += count(node->left);
        ret += count(node->right);
    }

    return ret;
}

template <typename T>
int BTree<T>::count() const
{
    return count(root());
}

template <typename T>
int BTree<T>::height(BTreeNode<T>* node) const
{
    int ret = 0;

    if(node != NULL)
    {
        ret = 1;
        int ret_l = height(node->left);
        int ret_r = height(node->right);

        if(ret_l < ret_r)
            ret += ret_r;
        else
            ret += ret_l;
    }

    return ret;
}

template <typename T>
int BTree<T>::height() const
{
    return height(root());
}

template <typename T>
void BTree<T>::free(BTreeNode<T>* node)
{
    if(node != NULL)
    {
        free(node->left);
        free(node->right);

        if(node->flag() == true)
        {
            delete node;
            node = NULL;
        }

    }
}

template <typename T>
void BTree<T>::clear()
{
    free(root());
    this->m_root = NULL;
}


}

#endif // BTREE_H
