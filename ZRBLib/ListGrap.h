#ifndef LISTGRAP_H
#define LISTGRAP_H

#include "Grap.h"
#include "Exception.h"
#include "DynamicArray.h"
#include "linklist.h"

namespace ZRBLib
{
template <typename V, typename E>
class ListGrap : public Grap<V, E>
{
protected:
    struct Vertex : public Object
    {
        V* data;
        LinkList<Edge<E>> edge;

        Vertex()
        {
            data = NULL;
        }
    };

    LinkList<Vertex*> m_list;

public:
    ListGrap(unsigned int n = 0);

    int addVertex();
    int addVertex(const V& value);
    void removeVertex();
    V getVertex(int i);
    bool getVertex(int i, V& value);
    bool setVertex(int i, const V& value);
    SharePointer< Array<int> > getAdjacent(int i);  //获取邻接的顶点集合
    E getEdge(int i, int j);
    bool getEdge(int i, int j, E& value);
    bool setEdge(int i, int j, const E& value);
    bool removeEdge(int i , int j);
    int vCount();   //amount of Vertex
    int eCount();   //amount of Edge
    int OD(int i);  //output degree
    int ID(int i);  //input degree

    ~ListGrap();
};

template <typename V, typename E>
ListGrap<V, E>::ListGrap(unsigned int n)    //O(n)
{
    for(int i = 0; i < n; i++)
        addVertex();
}

template <typename V, typename E>
ListGrap<V, E>::~ListGrap()         //O(n)
{
    while(m_list.length() > 0)
    {
        Vertex* toDel = m_list.get(0);

    //    toDel->edge.clear();    //delete edge
        m_list.remove(0);       //delete list Node
        delete toDel;           //delete vertex
    }
}

template <typename V, typename E>
int ListGrap<V, E>::addVertex()     //O(n)
{
    int ret = -1;

    Vertex* v = new Vertex();

    if(v != NULL)
    {
        m_list.insert(v);

        ret = m_list.length() - 1;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create Vertex..");
    }


    return ret;
}

template <typename V, typename E>
int ListGrap<V, E>::addVertex(const V& value)   //O(n)
{
    int ret = addVertex();

    if(ret >= 0)
        setVertex(ret, value);

    return ret;
}

template <typename V, typename E>
void ListGrap<V, E>::removeVertex()     //O(n2)
{
    if(m_list.length() > 0)
    {
        int index = m_list.length() - 1;
        Vertex* v = m_list.get(index);

        if(m_list.remove(index))
        {
            int i = 0;
            for(m_list.move(0); !m_list.end(); m_list.next(),++i)
            {
                int pos = m_list.current()->edge.find(Edge<E>(i, index));
                if(pos >= 0)
                {
                    m_list.current()->edge.remove(pos);
                }
            }
        }
      //  v->edge.clear();
        delete v->data;
        delete v;
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "no vertex in this grap");
    }
}

template <typename V, typename E>
V ListGrap<V, E>::getVertex(int i)  //O(n)
{
    V ret;

    if(!getVertex(i, ret))
    {
        THROW_EXCEPTION(InvalidParameterException, "index i is invaild..");
    }

    return ret;
}

template <typename V, typename E>
bool ListGrap<V, E>::getVertex(int i, V& value)     //O(n)
{
    bool ret = ((0 <= i) && (i < vCount()));

    if(ret)
    {
        Vertex* vertex = m_list.get(i);

        if(vertex->data != NULL)
        {
            value = *(vertex->data);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "no value assign to this vertex..");
        }
    }

    return ret;
}

template <typename V, typename E>
bool ListGrap<V, E>::setVertex(int i, const V& value)       //O(n)
{
    bool ret = ((0 <= i) && (i < vCount()));

    if(ret)
    {
        Vertex* vertex = m_list.get(i);
        V* data = vertex->data;

        if(data == NULL)
            data = new V();

        if(data != NULL)
        {
            *(data) = value;

            vertex->data = data;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create Vertex..");
        }
    }

    return ret;
}

template <typename V, typename E>
SharePointer< Array<int> > ListGrap<V, E>::getAdjacent(int i)   //O(n)
{
    DynamicArray<int>* ret = NULL;

    if((0 <= i) && (i < vCount()))
    {
       Vertex* v = m_list.get(i);

       ret = new DynamicArray<int>(v->edge.length());

       if(ret != NULL)
       {
            int k = 0;
            for(v->edge.move(0); !v->edge.end();v->edge.next(), ++k)
            {
                ret->set(k, v->edge.current().e);
            }
       }
       else
       {
           THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to ret ogject..");
       }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "index i is invaild");
    }


    return ret;
}

template <typename V, typename E>
E ListGrap<V, E>::getEdge(int i, int j)     //O(n)
{
    E ret;

    if(!getEdge(i, j, ret))
        THROW_EXCEPTION(InvalidParameterException, "edge <i,j> is invaild..");

    return ret;
}

template <typename V, typename E>
bool ListGrap<V, E>::getEdge(int i, int j, E& value)    //O(n)
{
    bool ret = (((0 <= i) && (i < vCount())) &&
                ((0 <= j) && (j < vCount())) );

    if(ret)
    {
        Vertex* v = m_list.get(i);
        int pos = v->edge.find(Edge<E>(i,j));

        if(pos >= 0)
        {
            value = v->edge.get(pos).data;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "no value assign to this edge");
        }
    }


    return ret;
}

template <typename V, typename E>
bool ListGrap<V, E>::setEdge(int i, int j, const E& value)      //O(n)
{
    bool ret = (((0 <= i) && (i < vCount())) &&
                ((0 <= j) && (j < vCount())) );

    if(ret)
    {
        Vertex* v = m_list.get(i);
        int pos = v->edge.find(Edge<E>(i, j));

        if(pos >= 0)
        {
            ret = v->edge.set(pos, Edge<E>(i, j, value));
        }
        else
        {
            ret = v->edge.insert(0, Edge<E>(i, j, value));
        }
    }

    return ret;
}

template <typename V, typename E>
bool ListGrap<V, E>::removeEdge(int i , int j)       //O(n)
{
    bool ret = (((0 <= i) && (i < vCount())) &&
                ((0 <= j) && (j < vCount())) );

    if(ret)
    {
        Vertex* v = m_list.get(i);
        int pos = v->edge.find(Edge<E>(i,j));

        if(pos >= 0)
        {
           ret = v->edge.remove(pos);
        }
    }

    return ret;
}

template <typename V, typename E>
int ListGrap<V, E>::vCount()   //amount of Vertex       O(1)
{
    return m_list.length();
}

template <typename V, typename E>
int ListGrap<V, E>::eCount()   //amount of Edge         O(n)
{
    int ret = 0;

    for(m_list.move(0); !m_list.end(); m_list.next())
    {
        ret += m_list.current()->edge.length();
    }

    return ret;
}

template <typename V, typename E>
int ListGrap<V, E>::OD(int i)  //output degree      O(n)
{
    int ret = 0;

    if((0 <= i) && (i < vCount()))
    {
        Vertex* v = m_list.get(i);

        ret = v->edge.length();
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "index i is invaild");
    }

    return ret;
}

template <typename V, typename E>
int ListGrap<V, E>::ID(int i)  //input degree       O(n2)
{
    int ret = 0;

    if((0 <= i) && (i < vCount()))
    {

        for(m_list.move(0); !m_list.end(); m_list.next())
        {
            LinkList< Edge<E> >& edge = m_list.current()->edge;

            for(edge.move(0); !edge.end(); edge.next())
            {
                if(i == edge.current().e)
                {
                    ret++;
                    break;
                }

            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "index i is invaild");
    }



    return ret;
}


}



#endif // LISTGRAP_H
