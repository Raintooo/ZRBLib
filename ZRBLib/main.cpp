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
   MatrixGrap<9, char, int> g;

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


   SharePointer<Array<Edge<int>>> sa = g.kruskal();

   for(int i = 0; i < sa->length(); i++)
       cout<< (*sa)[i].b<<" "<< (*sa)[i].e<< " "<< (*sa)[i].data<< endl;


   int a[] = {5,6,4,1,34,12,4,9,2,33,10,7};
   Sort::Shell(a, sizeof(a)/sizeof(int));
    return 0;

}





