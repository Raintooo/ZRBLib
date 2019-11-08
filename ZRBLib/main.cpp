#include <iostream>
#include "LinkStack.h"
#include "StaticQueue.h"
#include "LinkQueue.h"
#include "ZRBString.h"

using namespace std;
using namespace ZRBLib;


int main()
{
    String a("zrb.libzhurubai");

    cout<< a.indexof("zhu")<< endl;
    for(int i = 0; i < a.length(); i++)
    {
        cout<< a[i]<< endl;
    }
    return 0;

}



