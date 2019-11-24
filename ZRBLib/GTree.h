#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace ZRBLib
{
template <typename T>
class GTree : public Tree<T>
{
protected:
    LinkQueue< GTreeNode<T>* > m_queue;

    GTree(const GTree<T>& e);
    operator = (const GTree<T>& e);

    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const;
    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const;
    void free(GTreeNode<T>* node);
    void remove(GTreeNode<T>* node, GTree<T>*& ret);
    int count(GTreeNode<T>* node) const;
    int height(GTreeNode<T>* node) const;
    int degree(GTreeNode<T>* node) const;
public:
    GTree(){ }
    bool insert(TreeNode<T>* node);
    bool insert(const T& value, TreeNode<T>* parent);
    SharePointer< Tree<T> > remove(const T& value);
    SharePointer< Tree<T> > remove(TreeNode<T>* node);
    GTreeNode<T>* find(const T& value) const;
    GTreeNode<T>* find(TreeNode<T>* node) const;
    GTreeNode<T>* root() const;
    int degree() const;
    int count() const;
    int height() const;
    void clear();

    bool begin();
    bool end();
    bool next();
    T current();
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

    GTreeNode<T>* node = GTreeNode<T>::NewNode();
    if(node != NULL)
    {
        node->value = value;
        node->parent = parent;

        ret = insert(node);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No Enough Memory...");
    }

    return ret;
}

template <typename T>
void GTree<T>::remove(GTreeNode<T>* node, GTree<T>*& ret)
{
    ret = new GTree<T>();
    if(ret == NULL)
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create node...");
    }
    else
    {
        if(root() == node)
        {
            this->m_root = NULL;
        }
        else
        {
            LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;

            child.remove(child.find(node));
            node->parent = NULL;
        }

        ret->m_root = node;
    }
}

template <typename T>
SharePointer< Tree<T> > GTree<T>::remove(const T& value)
{
    GTree<T>* ret = NULL;
    GTreeNode<T>* node = find(value);

    if(node == NULL)
    {
        THROW_EXCEPTION(InvalidParameterException, "can`t find node value..");
    }
    else
    {
        remove(node, ret);
        m_queue.clear();
    }


    return ret;
}

template <typename T>
SharePointer< Tree<T> > GTree<T>::remove(TreeNode<T>* node)
{
    GTree<T>* ret = NULL;

    node = find(node);

    if(node == NULL)
    {
        THROW_EXCEPTION(InvalidParameterException, "this node not exit in this tree...");
    }
    else
    {
        remove(dynamic_cast<GTreeNode<T>*>(node), ret);
        m_queue.clear();
    }


    return ret;
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
    return dynamic_cast<GTreeNode<T>*>(this->m_root);
}

template <typename T>
int GTree<T>::degree(GTreeNode<T>* node) const
{
    int ret = 0;

    if(node != NULL)
    {
        ret = node->child.length();

        for(node->child.move(0); !node->child.end(); node->child.next())
        {
            int len = degree(node->child.current());

            if(len > ret)
                ret = len;
        }
    }

    return ret;
}

template <typename T>
int GTree<T>::degree() const
{
    return degree(root());
}

template <typename T>
int GTree<T>::height(GTreeNode<T>* node) const
{
    int ret = 0;

    if(node != NULL)
    {
        for(node->child.move(0); !node->child.end(); node->child.next())
        {
            int h = height(node->child.current());
            if(ret < h)
                ret = h;
        }
        ret += 1;
    }

    return ret;
}

template <typename T>
int GTree<T>::count(GTreeNode<T>* node) const
{
    int ret = 0;

    if(node != NULL)
    {
        ret = 1;
        for(node->child.move(0); !node->child.end(); node->child.next())
            ret += count(node->child.current());
    }

    return ret;
}

template <typename T>
int GTree<T>::count() const
{
    return count(root());
}

template <typename T>
int GTree<T>::height() const
{
    return height(root());
}

template <typename T>
void GTree<T>::free(GTreeNode<T>* node)
{
    if(node != NULL)
    {
        for(node->child.move(0); !node->child.end(); node->child.next())
        {
            free(node->child.current());
        }

        if(node->flag())
            delete node;
    }
}

template <typename T>
void GTree<T>::clear()
{
    free(root());
    this->m_root = NULL;
    m_queue.clear();

    return ;
}

template <typename T>
bool GTree<T>::begin()
{
    bool ret = (root() != NULL);

    if(ret)
    {
        m_queue.clear();
        m_queue.add(root());
    }

    return ret;
}

template <typename T>
bool GTree<T>::end()
{
    return (m_queue.length() == 0);
}

template <typename T>
bool GTree<T>::next()
{
    bool ret = (m_queue.length() > 0);

    if(ret)
    {
        GTreeNode<T>* node = m_queue.front();

        m_queue.remove();

        for(node->child.move(0); !node->child.end(); node->child.next())
        {
            m_queue.add(node->child.current());
        }
    }

    return ret;
}

template <typename T>
T GTree<T>::current()
{
    if(!end())
    {
        return m_queue.front()->value;
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "No value at current posistion...");
    }
}


}

#endif // GTREE_H
