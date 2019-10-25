#include <iostream>
#include "Object.h"
#include "Exception.h"
#include "Smartpointer.h"
#include "StaticList.h"
#include "DynamicList.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "linklist.h"
#include "StaticLinkList.h"
#include "SharePointer.h"
#include "CircleList.h"
#include "DualLinkList.h"

using namespace std;
using namespace ZRBLib;

void josep(int num, int pos, int step)
{
    CircleList<int> c;

    for(int i = 1; i <= num; i++)
    {
        c.insert(i);
    }

  //  cout<< c.test()<<endl;

}

int main()
{

    DualLinkList<int> t;

    for(int i = 0; i < 5; i++)
    {
        t.insert(0, i);
        t.insert(0, 5);
    }

    for(int i = 0; i < t.length(); i++)
    {
        cout<< t.get(i)<< endl;
    }

    cout<< "-------------------"<< endl;

    cout<< "-------------------"<< endl;
    t.move(t.length()-1);
    while(!t.end())
    {
        if(t.current() == 5)
        {
            cout<< t.current()<< endl;
            t.remove(t.find(t.current()));
        }
        else
        {
            t.pre();
        }

    }
    cout<< "-------------------"<< endl;
    return 0;
}

