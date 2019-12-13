#ifndef MATRIXGRAP_H
#define MATRIXGRAP_H

#include "Grap.h"
#include "Exception.h"
#include "DynamicArray.h"

namespace ZRBLib
{
template <int N, typename V, typename E>
class MatrixGrap : public Grap<V, E>
{
protected:
    V* m_vtertexs[N];
    E* m_edge[N][N];
    int m_eCount;   //amount of edge
public:
    MatrixGrap();

    V getVertex(int i);
    bool getVertex(int i, V& value);
    bool setVertex(int i, const V& value);
    SharePointer< Array<int> > getAdjacent(int i);  //获取邻接的顶点集合
    bool isAdjacent(int i, int j);
    E getEdge(int i, int j);
    bool getEdge(int i, int j, E& value);
    bool setEdge(int i, int j, const E& value);
    bool removeEdge(int i , int j);
    int vCount();   //amount of Vertex
    int eCount();   //amount of Edge
    int OD(int i);  //output degree
    int ID(int i);  //input degree

    ~MatrixGrap();
};

template <int N, typename V, typename E>
MatrixGrap<N, V, E>::MatrixGrap()
{
    for(int i = 0; i < vCount(); i++)
    {
        m_vtertexs[i] = NULL;
        for(int j = 0; j < vCount(); j++)
            m_edge[i][j] = NULL;
    }

    m_eCount = 0;
}

template <int N, typename V, typename E>
MatrixGrap<N, V, E>::~MatrixGrap()
{
    for(int i = 0; i < vCount(); i++)
    {
        for(int j = 0; j < vCount(); j++)
            delete m_edge[i][j];

        delete m_vtertexs[i];
    }
}

template <int N, typename V, typename E>
V MatrixGrap<N, V, E>::getVertex(int i)
{
    V ret;

    if(!getVertex(i, ret))
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invaild");
    }

     return ret;
}

template <int N, typename V, typename E>
bool MatrixGrap<N, V, E>::getVertex(int i, V& value)
{
    bool ret = ((0 <= i) && (i < vCount()));

    if(ret)
    {
        if(m_vtertexs[i] != NULL)
            value = *(m_vtertexs[i]);
        else
            THROW_EXCEPTION(InvalidOperationException, "No Value to assign to this vertex..");
    }

    return ret;
}

template <int N, typename V, typename E>
bool MatrixGrap<N, V, E>::setVertex(int i, const V& value)
{
    bool ret = ((0 <= i) && (i < vCount()));

    if(ret)
    {
        V* tmp = m_vtertexs[i];

        if(tmp == NULL)
            tmp = new V();

        if(tmp != NULL)
        {
            *tmp = value;   //value赋值可能出现异常, 利用临时变量保证异常安全

            m_vtertexs[i] = tmp;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No Value to assign to this vertex..");
        }
    }
    return ret;
}

template <int N, typename V, typename E>
bool MatrixGrap<N, V, E>::isAdjacent(int i, int j)
{
    return (i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()) && (m_edge[i][j] != NULL);
}

template <int N, typename V, typename E>
SharePointer< Array<int> > MatrixGrap<N, V, E>::getAdjacent(int i)
{
    DynamicArray<int>* ret = NULL;
    int n = 0;

    if((0 <= i) && (i < vCount()))
    {
        for(int j = 0; j < vCount(); j++)
        {
            if(m_edge[i][j] != NULL)
                n++;
        }

        ret = new DynamicArray<int>(n);
        if(ret != NULL)
        {
            int k = 0;
            for(int j = 0; j < vCount(); j++)
            {
                if(m_edge[i][j] != NULL)
                    ret->set(k++, j);
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to create new vertex value");
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invaild");
    }

    return ret;
}

template <int N, typename V, typename E>
E MatrixGrap<N, V, E>::getEdge(int i, int j)
{
    E ret;

    if(!getEdge(i, j, ret))
    {
        THROW_EXCEPTION(InvalidParameterException, "Index <i,j> is invaild");
    }

    return ret;
}

template <int N, typename V, typename E>
bool MatrixGrap<N, V, E>::getEdge(int i, int j, E& value)
{
    bool ret = (((0 <= i) && (i < vCount())) &&
                ((0 <= j) && (j < vCount())) );

    if(ret)
    {
        if(m_edge[i][j] != NULL)
            value = *(m_edge[i][j]);
        else
            THROW_EXCEPTION(InvalidParameterException, "No value assign to this edge..");
    }

    return ret;
}

template <int N, typename V, typename E>
bool MatrixGrap<N, V, E>::setEdge(int i, int j, const E& value)
{
    bool ret = (((0 <= i) && (i < vCount())) &&
                ((0 <= j) && (j < vCount())) );

    if(ret)
    {
        E* tmp = m_edge[i][j];

        if(tmp == NULL)
        {
            tmp = new E();

            if(tmp != NULL)
            {
                *(tmp) = value;
                m_edge[i][j] = tmp;

                m_eCount++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to create new edge value");
            }
        }
        else
        {
            *tmp = value;
        }
    }

    return ret;
}

template <int N, typename V, typename E>
bool MatrixGrap<N, V, E>::removeEdge(int i , int j)
{
    bool ret = (((0 <= i) && (i < vCount())) &&
                ((0 <= j) && (j < vCount())) );

    if(ret)
    {
        E* toDel = m_edge[i][j];

        if(toDel != NULL)
        {
            m_eCount--;

            m_edge[i][j] = NULL;

            delete toDel;
        }
    }

    return ret;
}

template <int N, typename V, typename E>
int MatrixGrap<N, V, E>::vCount()   //amount of Vertex
{
    return N;
}

template <int N, typename V, typename E>
int MatrixGrap<N, V, E>::eCount()   //amount of Edge
{
    return m_eCount;
}

template <int N, typename V, typename E>
int MatrixGrap<N, V, E>::OD(int i)  //output degree
{
    int ret = 0;

    if((0 <= i) && (i < vCount()))
    {
        for(int j = 0; j < vCount(); j++)
        {
            if(m_edge[i][j] != NULL)
                ret++;
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invaild");
    }
    return ret;
}

template <int N, typename V, typename E>
int MatrixGrap<N, V, E>::ID(int i)  //input degree
{
    int ret = 0;

    if((0 <= i) && (i < vCount()))
    {
        for(int j = 0; j < vCount(); j++)
        {
            if(m_edge[j][i] != NULL)
                ret++;
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invaild");
    }
    return ret;
}


}

#endif // MATRIXGRAP_H
