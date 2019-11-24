#ifndef C_LIST_H
#define C_LIST_H

#include <iostream>

namespace ZRBLib
{

typedef struct Node
{
    int value;
    Node* next;
}ZRB_Node;

ZRB_Node* Create_SingleList(int num)
{
    ZRB_Node* tmp = NULL;
    ZRB_Node* ret = (ZRB_Node*)malloc(sizeof(ZRB_Node));

    tmp = ret;

    for(int i = 0; i < num; i++)
    {
        ZRB_Node* node = (ZRB_Node*)malloc(sizeof(ZRB_Node));
        node->value = i;
        node->next = NULL;

        tmp->next = node;
        tmp = node;
    }

    return ret;
}

void print_SingleList(ZRB_Node* head)
{
    if(head != NULL)
    {
        ZRB_Node* tmp = head;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
            std::cout<< tmp->value<< std::endl;
        }
    }
}

void insert_SingleList(ZRB_Node* head, int value, int index)
{
    if((head->next != NULL) && (index >= 0))
    {
        ZRB_Node* tmp = head;
        ZRB_Node* node = (ZRB_Node*)malloc(sizeof(ZRB_Node));

        for(int i = 0; i < index; i++)
        {
            tmp = tmp->next;
        }

        node->next = tmp->next;
        node->value = value;

        tmp->next = node;
    }

}

ZRB_Node* Create_CircleList(int num)
{
    ZRB_Node* tmp = NULL;
    ZRB_Node* ret = (ZRB_Node*)malloc(sizeof(ZRB_Node));

    ret->next = ret;
    tmp = ret;

    for(int i = 0; i < num; i++)
    {
        ZRB_Node* node = (ZRB_Node*)malloc(sizeof(ZRB_Node));
        node->value = i;
        node->next = tmp->next;

        tmp->next = node;
        tmp = node;
    }

    return ret;
}

void insert_CircleList(ZRB_Node* head, int value, int index)
{
    if(head->next != NULL)
    {
        ZRB_Node* tmp = head;
        ZRB_Node* node = (ZRB_Node*)malloc(sizeof(ZRB_Node));

        for(int i = 0; i < index; i++)
        {
            tmp = tmp->next;
        }

        node->value = value;
        node->next = tmp->next;

        tmp->next = node;
    }
}



}

#endif // C_LIST_H
