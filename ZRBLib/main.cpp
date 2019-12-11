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
   const char* VD = "ABCDEFGHI";

   for(int i = 0; i < strlen(VD); i++)
       g.setVertex(i, VD[i]);


   g.setEdge(0, 1, 0);
   g.setEdge(1, 0, 0);

   g.setEdge(0, 3, 0);
   g.setEdge(3, 0, 0);

   g.setEdge(0, 4, 0);
   g.setEdge(4, 0, 0);

   g.setEdge(1, 2, 0);
   g.setEdge(2, 1, 0);

   g.setEdge(1, 4, 0);
   g.setEdge(4, 1, 0);

   g.setEdge(3, 6, 0);
   g.setEdge(6, 3, 0);

   g.setEdge(4, 6, 0);
   g.setEdge(6, 4, 0);

   g.setEdge(2, 5, 0);
   g.setEdge(5, 2, 0);

   g.setEdge(6, 7, 0);
   g.setEdge(7, 6, 0);

   g.setEdge(7, 8, 0);
   g.setEdge(8, 7, 0);

   SharePointer<Array<int>> sa = g.DFS(0);

   for(int i = 0; i < sa->length(); i++)
       cout<< (*sa)[i]<<" ";

   cout<< endl;
   DFS(g,0);


    return 0;

}





