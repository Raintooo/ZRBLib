#include <iostream>
#include "LinkStack.h"
#include "StaticQueue.h"
#include "LinkQueue.h"

using namespace std;
using namespace ZRBLib;

class Test
{

public:
    Test()
    {
        cout<< "test"<< endl;
    }
    ~Test()
    {
        cout<< "~test"<< endl;
    }
};

int main()
{

    LinkQueue<int> t;
    for(int i = 0; i < 5; i++)
    {
        t.add(i);
    }
    for(int i = 0; i < 5; i++)
    {
        cout<< t.front()<< endl;
        t.remove();
    }



    return 0;

}



