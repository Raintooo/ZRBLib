#include <iostream>
#include <cstring>
#include "LinkStack.h"
#include "StaticQueue.h"
#include "LinkQueue.h"
#include "ZRBString.h"
#include "linklist.h"
#include "Sort.h"
#include "C_Sort.h"
#include "GTree.h"
#include "singleton.h"
#include "c_list.h"
#include "BTree.h"
#include "C_BTree.h"
#include "BTree_pratice.h"
#include "Grap.h"
#include "MatrixGrap.h"
#include "ListGrap.h"
#include "Queen.h"

using namespace std;
using namespace ZRBLib;

int f(int x)
{
    return ((x>0)?x*f(x-1):2);
}

template <typename T, typename E>
Grap<T, E>& grap_2()
{
    static ListGrap<T, E> g(3);

    g.setEdge(0, 1, 4);
    g.setEdge(0, 2, 11);

    g.setEdge(1, 2, 2);
    g.setEdge(1, 0, 6);

    g.setEdge(2, 0, 3);

    return g;
}

void Solution(int* array, int len);

int main()
{

//    Grap<int, int>& g = grap_2<int, int>();

//   SharePointer<Array<int>> sa = g.floyd(0, 2, 65535);

//   for(int i = 0; i < sa->length(); i++)
//       cout<< (*sa)[i]<< endl;
//3, 18, 7, 14, 10, 12, 23, 41, 16, 24
    int a[] = {1, 3, 5, 4};
    Solution(a, sizeof(a)/sizeof(int));

}


template <typename T, typename E>
Grap<T, E>& grap_1()
{
   static MatrixGrap<9, T, E> g;

   g.setEdge(0, 1, 10);
   g.setEdge(1, 0, 10);

   g.setEdge(0, 5, 11);
   g.setEdge(5, 0, 11);

   g.setEdge(1, 2, 18);
   g.setEdge(2, 1, 18);

   g.setEdge(1, 6, 16);
   g.setEdge(6, 1, 16);

   g.setEdge(1, 8, 12);
   g.setEdge(8, 1, 12);

   g.setEdge(2, 8, 8);
   g.setEdge(8, 2, 8);

   g.setEdge(2, 3, 22);
   g.setEdge(3, 2, 22);

   g.setEdge(8, 3, 21);
   g.setEdge(3, 8, 21);

   g.setEdge(6, 3, 24);
   g.setEdge(3, 6, 24);

   g.setEdge(3, 7, 16);
   g.setEdge(7, 3, 16);

   g.setEdge(6, 7, 19);
   g.setEdge(7, 6, 19);

   g.setEdge(3, 4, 20);
   g.setEdge(4, 3, 20);

   g.setEdge(7, 4, 7);
   g.setEdge(4, 7, 7);

   g.setEdge(5, 4, 26);
   g.setEdge(4, 5, 26);

   g.setEdge(5, 6, 17);
   g.setEdge(6, 5, 17);

   return g;
}


int search_max_path(Grap<int, int>& g, int v, Array<int>& count, Array< LinkList<int>* >& path, Array<bool>& mark)
{
    int ret = 0;
    SharePointer< Array<int> > aj = g.getAdjacent(v);

    for(int i = 0; i < aj->length(); i++)
    {
        int num = 0;

        if(!mark[(*aj)[i]])
        {
            num = search_max_path(g, (*aj)[i], count, path, mark);
        }
        else
        {
            num = count[(*aj)[i]];
        }

        if(ret < num)
        {
            ret = num;
        }
    }

     for(int i = 0; i < aj->length(); i++)  //可能存在多条长度相同的 不下降序列 用链表方式存储
     {
         if(ret == count[(*aj)[i]])
         {
             path[v]->insert((*aj)[i]);
         }
     }

    ret++;
    count[v] = ret;
    mark[v] = true;

    return ret;
}


SharePointer< Grap<int, int> > Create_Grap(int* array, int len)
{
    ListGrap<int, int>* ret = new ListGrap<int, int>(len);

    for(int i = 0; i < len; i++)
    {
        ret->setVertex(i, array[i]);
    }
    for(int i = 0; i < len; i++)
    {
        for(int j = i+1; j < len; j++)
        {
            if(array[i] <= array[j])
                ret->setEdge(i, j, 1);
        }
    }
    return ret;
}

void init_array(Array<int>& count, Array< LinkList<int>* >& path, Array<bool>& mark)
{
    for(int i = 0; i < count.length(); i++)
    {
        count[i] = 0;
    }
    for(int i = 0; i < path.length(); i++)
    {
        path[i] = new LinkList<int>();
    }
    for(int i = 0; i < mark.length(); i++)
    {
        mark[i] = false;
    }
}

void search_max_path(Grap<int, int>& g, Array<int>& count, Array< LinkList<int>* >& path, Array<bool>& mark)
{
    for(int i = 0; i < g.vCount(); i++)
    {
        if(!mark[i])
            search_max_path(g, i, count, path, mark);
    }
}

/*
  用回溯方式遍历 不下降序列
*/
void print_path(Grap<int, int> &g, int v, Array< LinkList<int>* > &path, LinkList<int>& cp)
{
    cp.insert(v);

    if(path[v]->length() > 0)
    {
        for(path[v]->move(0); !path[v]->end(); path[v]->next())
        {
            print_path(g, path[v]->current(), path, cp);
        }
    }
    else
    {
        for(cp.move(0); !cp.end(); cp.next())
        {
            cout<< g.getVertex(cp.current())<< "-";
        }
        cout<< endl;
    }

    cp.remove(cp.length()-1);   //找到一条不下降序列后 将最后一个去除 回溯再次遍历是否还有长度相同不下降序列
}

void print_max_path(Grap<int, int> &g, Array<int> &count, Array< LinkList<int>* > &path)
{
    int max = 0;
    LinkList<int> cp;

    for(int i = 0; i < count.length(); i++)
    {
        if(max < count[i])
            max = count[i];
    }

    for(int j = 0; j < count.length(); j++)
    {
        if(max == count[j])
        {
            print_path(g, j, path, cp);
        }
    }
}

void Solution(int* array, int len)
{
    DynamicArray<int> count(len);
    DynamicArray< LinkList<int>* > path(len);
    DynamicArray<bool> mark(len);

    SharePointer< Grap<int, int> > g;

    g = Create_Grap(array, len);

    init_array(count, path, mark);

    search_max_path(*g, count, path, mark);

    print_max_path(*g, count, path);

}




