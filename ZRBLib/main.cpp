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

using namespace std;
using namespace ZRBLib;

class Test : public Object
{
int i;
public:
    int value;
    Test() : value(1)
    {
        cout<< "new Test"<< endl;
    }
    ~Test()
    {
        cout<< "new ~Test"<< endl;
    }

};

int main()
{

   // SharePointer<Test> l = new Test();
    SharePointer<Test> l = new Test();
    SharePointer<Test> l1 = l;
    SharePointer<Test> l2 = NULL;

    l2 = l1;

    cout<<l->value << endl;
    cout<<l1->value << endl;
    cout<<l2->value << endl;


    cout<< "------------"<< endl;

    if(l == l1)



    return 0;
}

