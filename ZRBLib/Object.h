﻿#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <cstdlib>

namespace ZRBLib {


class Object
{
public:
    void* operator new (unsigned int size) throw();
    void operator delete (void* p);
    void* operator new[](unsigned int size) throw();
    void operator delete[](void* p);
    bool operator == (const Object& obj);
    bool operator != (const Object& obj);
    virtual ~Object() = 0;
};

}

#endif // OBJECT_H
