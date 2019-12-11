#ifndef GRAP_H
#define GRAP_H

#include "Object.h"
#include "SharePointer.h"
#include "Array.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"

namespace ZRBLib
{

template <typename E>
struct Edge : public Object
{
    int b;  //start point index
    int e;  //end point index
    E data;

    Edge(int i = -1, int j = -1)
    {
        b = i;
        e = j;
    }

    Edge(int i, int j, const E& value)
    {
        b = i;
        e = j;
        data = value;
    }

    bool operator ==(const Edge<E>& obj)
    {
        return (b == obj.b) && (e == obj.e);
    }

    bool operator !=(const Edge<E>& obj)
    {
        return !(*this == obj);
    }
};

template <typename V, typename E> //V : Vertex(顶点)  E : Edge(边)
class Grap : public Object
{
protected:
    template <typename T>
    DynamicArray<T>* toArray(LinkQueue<T>& q)
    {
        DynamicArray<T>* ret = new DynamicArray<T>(q.length());

        if(ret != NULL)
        {
            for(int i = 0; i < ret->length(); i++)
            {
                ret->set(i, q.front());
                q.remove();
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no enough memory..");
        }

        return ret;
    }

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

    SharePointer< Array<int> > BFS(int i)   //广度优先
    {
        DynamicArray<int>* ret = NULL;
        if((0 <= i) && (i < vCount()))
        {
            LinkQueue<int> q;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());

            for(int j = 0; j < visited.length(); j++)
                visited[j] = false;

            q.add(i);

            while(q.length() > 0)
            {
                int v = q.front();
                q.remove();

                if(visited[v] == false)
                {
                    SharePointer< Array<int> > aj = getAdjacent(v);

                    for(int j = 0; j < aj->length(); j++)
                    {
                        q.add((*aj)[j]);
                    }
                    r.add(v);
                    visited[v] = true;
                }
            }
            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "index i is invaild");
        }


        return ret;
    }

    SharePointer< Array<int> > DFS(int i)
    {
        DynamicArray<int>* ret = NULL;

        if((0 <= i) && (i < vCount()))
        {
            LinkStack<int> stack;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());

            for(int j = 0; j < visited.length(); j++)
                visited[j] = false;

            stack.push(i);

            while(stack.size())
            {
                int v = stack.top();
                stack.pop();

                if(visited[v] == false)
                {
                    SharePointer< Array<int> > aj = getAdjacent(v);
                    for(int j = aj->length()-1; j >= 0; j--)
                        stack.push((*aj)[j]);

                    r.add(v);
                    visited[v] = true;
                }
            }

            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "index i is invaild");
        }

        return ret;
    }

};
template <typename V, typename E>
void DFS(Grap<V, E>& g, int v, DynamicArray<bool>& visted)  //recursion
{
    if((0 <= v) && (v < g.vCount()))
    {
        cout<< v<< " ";

        visted[v] = true;

        SharePointer<Array<int>> aj = g.getAdjacent(v);
        for(int j = 0; j < aj->length(); j++)
        {
            if(visted[(*aj)[j]] == false)
            {
                DFS(g, (*aj)[j], visted);
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "index i is invaild");
    }
}

template <typename V, typename E>
void DFS(Grap<V, E>& g, int v)
{
    DynamicArray<bool> visted(g.vCount());

    for(int i = 0; i < visted.length(); i++)
        visted[i] = false;

    DFS(g, v, visted);
}

}

#endif // GRAP_H
