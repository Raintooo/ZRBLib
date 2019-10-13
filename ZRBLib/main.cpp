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

using namespace std;
using namespace ZRBLib;

class Test : public Object
{
int i;
public:
    Test(int a = 0)
    {
        cout<< "new Test"<< endl;
        i = a;
    }
    bool operator == (const Test& e)
    {
        return (i == e.i);
    }
};

int main()
{
    StaticLinkList<int, 5> l;

    for(int i = 0; i < 5; i++)
    {
        l.insert(0, i);
    }

    l.remove(2);

    for(l.move(0, 1); !l.end(); l.next())
    {
        cout<< l.current()<< endl;
    }

    cout<< "------------"<< endl;



    return 0;
}

