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

class Test
{
public:
    Test()
    {
        throw 0;
    }
};

int main()
{
    LinkList<Test> ll;
    LinkList<int> l;

/*
    for(int i = 0; i < 5; i++)
    {
        l.insert(i, i);
    }

    for(int i = 0; i < l.length(); i++)
    {
        cout<< l.get(i)<< endl;
    }
    cout<< "------------"<< endl;

    l.remove(0);
    for(int i = 0; i < l.length(); i++)
    {
        cout<< l.get(i)<< endl;
    }
*/
    return 0;
}

