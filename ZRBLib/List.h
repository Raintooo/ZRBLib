#ifndef LIST_H
#define LIST_H

#include "Object.h"

namespace ZRBLib
{

template <typename T>
class List : public Object
{
protected:
    List(const List& e);
    List& operator = (const List& e);
public:
    List() {};
    virtual bool insert(int index, const T& e) = 0;
    virtual bool remove(int index) = 0;
    virtual bool set(int index, const T& e) = 0;
    virtual bool get(int index, T& e) const = 0;
    virtual int length() = 0;
    virtual void clear() = 0;
};

}


#endif // LIST_H
