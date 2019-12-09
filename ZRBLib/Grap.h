#ifndef GRAP_H
#define GRAP_H

#include "Object.h"
#include "SharePointer.h"
#include "Array.h"

namespace ZRBLib
{

template <typename V, typename E> //V : Vertex(顶点)  E : Edge(边)
class Grap : public Object
{
public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V& value) = 0;
    virtual bool setVertex(int i, const V& value) = 0;
    virtual SharePointer< Array<int> > getAdjacent(int i) = 0;
    virtual E getEdge(int i, int j) = 0;
    virtual bool getEdge(int i, int j, E& value) = 0;
    virtual bool setEdge(int i, int j, const E& value) = 0;
    virtual bool removeEdge(int i , int j) = 0;
    virtual int vCount() = 0;   //amount of Vertex
    virtual int eCount() = 0;   //amount of Edge
    virtual int OD(int i) = 0;  //output degree
    virtual int ID(int i) = 0;  //input degree

    virtual int TD(int i)
    {
        return OD(i) + ID(i);
    }

};


}

#endif // GRAP_H
