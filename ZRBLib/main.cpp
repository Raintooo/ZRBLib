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

int* get_pmt(const char* p)
{
    int len = strlen(p);
    int* ret = static_cast<int*>(malloc(sizeof(int) * len));

    if(ret != NULL)
    {
        int ll = 0;              //这里ll值是前后缀交集的最大长度
        ret[0] = 0;

        for(int i = 1; i < len; i++)
        {
            while((ll > 0) && (p[ll] != p[i]))
            {
                ll = ret[ll-1];         //这里匹配不上就找 当前匹配时的重叠部分
            }

            if(p[ll] == p[i])
            {
                ll++;
            }
            ret[i] = ll;
        }
    }
    return ret;
}

int kmp(const char* s, const char* p)
{
    int ret = -1;
    int sl = strlen(s);
    int pl = strlen(p);
    int* pmt = get_pmt(p);


    if((pmt != NULL) && (pl > 0) && (pl <= sl))
    {
        for(int i = 0, j = 0; i < sl; i++)
        {
            while((j > 0) && (p[j] != s[i]))
            {
                j = j - (j - pmt[j-1]);//pmt[j-1];
            }
            if(p[j] == s[i])
            {
                j++;
            }
            if(j == pl)
            {
                ret = i + 1 - pl;
                break;
            }

        }

    }

    free(pmt);

    return ret;
}

int f(int x)
{
    return ((x>0)?x*f(x-1):2);
}


class A
{};

int main()
{
   MatrixGrap<4, char, int> g;

   g.setEdge(0, 1, 1);
   g.setEdge(1, 0, 1);

   g.setEdge(0, 2, 3);
   g.setEdge(2, 0, 3);

   g.setEdge(1, 2, 1);
   g.setEdge(2, 1, 1);

   g.setEdge(1, 3, 4);
   g.setEdge(3, 1, 4);

   g.setEdge(2, 3, 5);
   g.setEdge(3, 2, 5);


   SharePointer<Array<Edge<int>>> sa = g.Prim(6666);

   for(int i = 0; i < sa->length(); i++)
       cout<< (*sa)[i].b<<" "<< (*sa)[i].e<< " "<< (*sa)[i].data<< endl;


    return 0;

}





