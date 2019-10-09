#include <iostream>
#include "Object.h"
#include "Exception.h"
#include "Smartpointer.h"
#include "StaticList.h"
#include "DynamicList.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "linklist.h"

using namespace std;
using namespace ZRBLib;

class Test : public Object
{
int i;
public:
    Test(int a = 0)
    {
        i = a;
    }
    bool operator == (const Test& e)
    {
        return (i == e.i);
    }
};

int main()
{
    LinkList<Test> l;
    Test t1(1);
    Test t2(2);
    Test t3(3);

    l.insert(t1);
    l.insert(t2);
    l.insert(t3);

    cout<< l.find(t2)<< endl;
/*
    for(int i = 0; i < 5; i++)
    {
        l.insert(0, i);
    }

    for(int i = 0; i < l.length(); i++)
    {
        cout<< l.get(i)<< endl;
    }
    cout<< "------------"<< endl;

    cout<< l.find(-3)<< endl;
*/
    return 0;
}

