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

void HanoTower(int n, char a, char b, char c)   //n 木块数量
{
    if(n == 1)
    {
        cout<< a << "-->"<< c<< endl;
    }
    else
    {
        HanoTower(n-1, a, c, b);    //将 n-1 个 a 借助 c 移动到b
        HanoTower(1, a, b, c);      //将最后一个 a 移动到 c
        HanoTower(n-1, b, a, c);    //将 b 借助 a 移动到 c
    }
}

/*
 * 全排列
*/
void permutation(char* s, char* e)
{
    if(*s == '\0')
    {
        cout<< e<< endl;
    }
    else
    {
        int len = strlen(s);
        for(int i = 0; i < len; i++)
        {
            swap(s[0], s[i]);
            permutation(s+1, e);
            swap(s[0], s[i]);
        }
    }
}

template <int SIZE>
class Queen : public Object
{
    enum { N = SIZE + 2};
    struct Pos : public Object
    {
        Pos(int _x = 0, int _y = 0) : x(_x), y(_y){ }
        int x;
        int y;
    };

    int m_chessboard[N][N];
    Pos m_direction[3];
    int m_count;
    LinkList<Pos> m_list;

    void init()
    {
        m_count = 0;

        for(int i = 0; i < N; i+=N-1)
        {
            for(int j = 0; j < N; j++)
            {
                m_chessboard[i][j] = 2;
                m_chessboard[j][i] = 2;
            }
        }
        for(int i = 1; i <= SIZE; i++)
        {
            for(int j = 1; j <= SIZE; j++)
            {
                m_chessboard[i][j] = 0;
            }
        }

        m_direction[0].x =-1;
        m_direction[0].y =-1;
        //向下
        m_direction[1].x =0;
        m_direction[1].y =-1;
        //右下角
        m_direction[2].x =1;
        m_direction[2].y =-1;
    }

    void print()
    {
        for(m_list.move(0); !m_list.end(); m_list.next())
        {
            cout<< "( "<< m_list.current().x<< ","<< m_list.current().y<< " )  ";
        }
        cout<< endl;
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                switch (m_chessboard[i][j])
                {
                    case 0: cout<< "  "; break;
                    case 1: cout<< "# "; break;
                    case 2: cout<< "* "; break;
                    default: break;
                }
            }
            cout<< endl;
        }
    }

    bool check(int x, int y, int dir)
    {
        bool flag = true;

        do
        {
            x += m_direction[dir].x;
            y += m_direction[dir].y;
            flag = flag && (m_chessboard[x][y] == 0);
        }while(flag);

        bool ret = (m_chessboard[x][y] == 2);
        return ret;
    }

    void run(int j)
    {
        if(j <= SIZE)
        {
            for(int i = 1; i <= SIZE; i++)
            {
                if(check(i, j, 0) && check(i, j, 1) && check(i, j, 2))
                {
                    m_chessboard[i][j] = 1;
                    m_list.insert(Pos(i , j));

                    run(j + 1);

                    m_chessboard[i][j] = 0;
                    m_list.remove(m_list.length() - 1);
                }
            }
        }
        else
        {
            m_count++;
            print();
        }
    }

public:
    Queen()
    {
        init();
    }
    void run()
    {
        run(1);
        cout<< "Total "<< m_count<< endl;
    }
};

int main()
{
    BTree<int> t;
    BTreeNode<int>* node = NULL;
    BTreeNode<int> A;

    A.value = 1;
    A.parent = NULL;

    t.insert(&A);

    node = t.find(1);
    t.insert(2, node);
    t.insert(3, node);

    node = t.find(2);
    t.insert(4, node);
    t.insert(5, node);

    node = t.find(3);
    t.insert(6, node);
    t.insert(7, node);

    node = t.find(4);
    t.insert(8, node);
    t.insert(9, node);

    node = t.find(5);
    t.insert(10, node);

    node = t.find(6);
    t.insert(11, node, LEFT);

//    SharePointer< Tree<int> > sp = t.remove(3);

//    SharePointer<Array<int>> sp = t.traversal(PostOrder);
//    SharePointer<BTree<int>> bclone = t.clone();
//    int a[] = {8, 9, 10, 7};

//    for(int i = 0; i < 4; i++)
//    {
//        TreeNode<int>* node = bclone->find(a[i]);
//        while(node)
//        {
//            cout<< node->value<< "-";
//            node = node->parent;
//        }
//        cout<< endl;
//    }

//    cout<< "--------"<< endl;


//    for(int i = 0; i < 5; i++)
//    {
//        TreeNode<int>* node = t.find(a[i]);
//        while(node)
//        {
//            cout<< node->value<< "-";
//            node = node->parent;
//        }
//        cout<< endl;
//    }

    SharePointer<Array<int>> sp = t.traversal(PreOrder);
    for(int i = 0; i < (*sp).length(); i++)
        cout<< (*sp)[i]<<"-";
    cout<< "-----"<< endl;

    BTreeNode<int>* head = t.thread(PreOrder);
    while(head != NULL)
    {
        cout<< head->value<< "-";
        head = head->right;
    }

    cout<< endl;



    BTree<int> nt;

    nt.insert(0, NULL);

    node = nt.find(0);
    nt.insert(6, node);
    nt.insert(2, node);

    node = nt.find(2);
    nt.insert(7, node);
    nt.insert(8, node);


    SharePointer<BTree<int>> bt = t.add(nt);
    sp = bt->traversal(PreOrder);
    for(int i = 0; i < (*sp).length(); i++)
        cout<< (*sp)[i]<<"-";
    cout<< "-----"<< endl;

//    for(bt->begin(); !bt->end(); bt->next())
//    {
//        cout<< bt->current()<< "-";
//    }

    return 0;

}





