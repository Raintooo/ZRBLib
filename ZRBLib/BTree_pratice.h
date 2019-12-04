#ifndef BTREE_PRATICE_H
#define BTREE_PRATICE_H

#include "BTreeNode.h"

namespace ZRBLib
{
template <typename T>
BTreeNode<T>* createTree()
{
    static BTreeNode<T> ns[9];

    for(int i = 0; i < 9; i++)
    {
        ns[i].value = i;
        ns[i].left = NULL;
        ns[i].right = NULL;
        ns[i].parent = NULL;
    }

    ns[0].left = &ns[1];
    ns[0].right = &ns[2];

    ns[1].parent = &ns[0];
    ns[1].left = &ns[3];

    ns[3].parent = &ns[1];
    ns[3].right = &ns[6];

    ns[2].parent = &ns[0];
    ns[2].left = &ns[4];
    ns[2].right = &ns[5];

    ns[4].parent = &ns[2];
    ns[4].left = &ns[7];

    ns[5].parent = &ns[2];
    ns[5].left = &ns[8];

    ns[7].parent = &ns[4];
    ns[8].parent = &ns[5];

    return ns;
}

template <typename T>
void PrintInOrderTraverse(const BTreeNode<T>* root)
{
    if(root == NULL)
        return;
    PrintInOrderTraverse(root->left);
    std::cout<<root->value<<" ";
    PrintInOrderTraverse(root->right);
}


template <typename T>
BTreeNode<T>* DelOld(BTreeNode<T>* node)
{
    BTreeNode<T>* ret = NULL;

    if(node == NULL)
    {
        return NULL;
    }
    else
    {
        if(((node->left != NULL) && (node->right == NULL)) ||
           ((node->right != NULL) && (node->left == NULL)))
        {
            BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);
            BTreeNode<T>* node_child = (node->left != NULL) ? node->left : node->right;

            if(parent != NULL)
            {
                BTreeNode<T>*& parent_child = (parent->left == node) ? parent->left : parent->right;
                parent_child = node_child;
                node_child->parent = parent;
            }
            else
            {
                node_child->parent = NULL; //替换根节点
            }

            if(node->flag())
                delete node;

            ret = DelOld(node_child);

        }
        else
        {
            DelOld(node->left);
            DelOld(node->right);

            ret = node;
        }
    }

    return ret;
}

template <typename T>
BTreeNode<T>* DelOld2(BTreeNode<T>*& node) //No parent pointer
{
    BTreeNode<T>* ret = NULL;

    if(node == NULL)
    {
        return NULL;
    }
    else
    {
        if(((node->left != NULL) && (node->right == NULL)) ||
           ((node->right != NULL) && (node->left == NULL)))
        {
            BTreeNode<T>* node_child = (node->left != NULL) ? node->left : node->right;

            if(node->flag())
                delete node;

            node = node_child;

            ret = DelOld2(node);
        }
        else
        {
            DelOld2(node->left);
            DelOld2(node->right);

            ret = node;
        }
    }
    return ret;
}

void test()
{
    BTreeNode<int>* t = createTree<int>();

    PrintInOrderTraverse(t);

    t = DelOld2(t);

    std::cout<< std::endl;
    PrintInOrderTraverse(t);
}



}

#endif // BTREE_PRATICE_H
