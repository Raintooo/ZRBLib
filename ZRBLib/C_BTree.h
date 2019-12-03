#ifndef C_BTREE_H
#define C_BTREE_H

#include <iostream>

namespace ZRBLib
{
typedef struct C_BNode
{
    C_BNode* left;
    C_BNode* right;
    char value;
}C_BNode;

void PreOrderTraverse(const C_BNode* root)
{
    if(root == NULL)
        return;
    std::cout<<root->value<<" ";
    PreOrderTraverse(root->left);
    PreOrderTraverse(root->right);
}

static C_BNode* _CreateBTree(char *str, int* currpos)
{
    C_BNode* ret = NULL;
    if(*(str + (*currpos)) != '#')
    {
        ret = reinterpret_cast<C_BNode*>(malloc(sizeof(C_BNode)));
        if(ret != NULL)
        {
            ret->value = *(str + (*currpos));
            *currpos += 1;
            ret->left = _CreateBTree(str, currpos);
            ret->right = _CreateBTree(str, currpos);
        }
        else
        {
            return NULL;
        }

    }
    else if(*(str + (*currpos)) == '#')
    {
        *currpos += 1;
    }

    return ret;
}

C_BNode* CreateBTree(char *str)
{
    int curpos = 0;
    return _CreateBTree(str, &curpos);
}


}

#endif // C_BTREE_H
