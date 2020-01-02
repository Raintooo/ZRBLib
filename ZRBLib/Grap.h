#ifndef GRAP_H
#define GRAP_H

#include "Object.h"
#include "SharePointer.h"
#include "Array.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"
#include "Sort.h"

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
    bool operator >(const Edge<E>& obj)
    {
        return (this->data > obj.data);
    }
    bool operator <(const Edge<E>& obj)
    {
        return (this->data < obj.data);
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
    virtual bool isAdjacent(int i, int j) = 0;
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

    int find(Array<int>& p, int val)
    {
        while(p[val] != -1)
            val = p[val];

        return val;
    }

    bool asUndireted()  //判断是否可作为无向图
    {
        bool ret = true;

        for(int i = 0; i < vCount(); i++)
        {
            for(int j = 0; j < vCount(); j++)
            {
                if(isAdjacent(i, j))
                {
                    ret = ret && isAdjacent(j, i) && (getEdge(i, j) == getEdge(j, i));
                }
            }
        }


        return ret;
    }

    SharePointer< Array<int> > Dijkstra(int i, int j, const E& LIMIT)
    {
        LinkQueue<int> ret;

        if((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
        {
            DynamicArray<E> dist(vCount());
            DynamicArray<int> path(vCount());
            DynamicArray<bool> mark(vCount());

            for(int w = 0; w < vCount(); w++)   //init
            {
                mark[w] = false;
                path[w] = -1;

                dist[w] = isAdjacent(i, w) ? (path[w] = i, getEdge(i, w)) : LIMIT;  //把初始顶点的邻接顶点加入到dist 数组 并加入对应权值 更新 path 数组
            }

            mark[i] = true;

            for(int k = 0; k < vCount(); k++)
            {
                E m = LIMIT;
                int u = -1;

                for(int w = 0; w < vCount(); w++)   //选取最小权值的顶点
                {
                    if(!mark[w] && (dist[w] < m))
                    {
                        m = dist[w];
                        u = w;
                    }
                }

                if(u == -1)
                    break;

                mark[u] = true;

                for(int w = 0; w < vCount(); w++)
                {
                    if(!mark[w] && isAdjacent(u, w) && (dist[u] + getEdge(u, w) < dist[w])) //将选取的顶点加上 下一顶点 与原路径权值比较 取最小权值 并刷新path 和 dist
                    {
                        dist[w] = dist[u] + getEdge(u, w);
                        path[w] = u;
                    }
                }
            }

            LinkStack<int> s;

            s.push(j);  //把最后的顶点先入栈

            for(int k = path[j]; k != -1; k = path[k])
            {
                s.push(k);
            }

            while(s.size() > 0)
            {
                ret.add(s.top());
                s.pop();
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "index <i,j> is invaild");
        }

        if(ret.length() < 2) // < 2 说明图 i -> j 不可达 最短路径至少2个顶点
        {
            THROW_EXCEPTION(ArithmeticException, "no path from i to j");
        }

        return toArray(ret);
    }

    SharePointer<Array<int>> floyd(int x, int y, const E& LIMIT)
    {
        LinkQueue<int> ret;

        if((0 <= x) && (x < vCount()) && (0 <= y) && (y < vCount()))
        {
            DynamicArray< DynamicArray<E> > dst(vCount());
            DynamicArray< DynamicArray<int> > path(vCount());

            for(int k = 0; k < vCount(); k++)
            {
                dst[k].resize(vCount());
                path[k].resize(vCount());
            }

            for(int i = 0; i < vCount(); i++)
            {
                for(int j = 0; j < vCount(); j++)
                {
                    path[i][j] = -1;
                    dst[i][j] = isAdjacent(i, j) ? (path[i][j] = j, getEdge(i, j)) : LIMIT;
                }
            }

            for(int k = 0; k < vCount(); k++)
            {
                for(int i = 0; i < vCount(); i++)
                {
                    for(int j = 0; j < vCount(); j++)
                    {
                        if(dst[i][k] + dst[k][j] < dst[i][j])
                        {
                            dst[i][j] = dst[i][k] + dst[k][j];
                            path[i][j] = path[i][k];            //path[i][k] 记录 i -> j 最小路径的第j个顶点
                        }
                    }
                }

            }

            while((x != -1) && (x != y))
            {
                ret.add(x);
                x = path[x][y];
            }
            if(x != -1)
                ret.add(x);


            if(ret.length() < 2) // < 2 说明图 i -> j 不可达 最短路径至少2个顶点
            {
                THROW_EXCEPTION(ArithmeticException, "no path from x to y");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "index <i,j> is invaild");
        }


        return toArray(ret);
    }


    SharePointer<Array<Edge<E>>> getUndiretedEdge()
    {
        DynamicArray<Edge<E>>* ret = NULL;

        if(asUndireted())
        {
            LinkQueue<Edge<E>> queue;
            for(int i = 0; i < vCount(); i++)
            {
                for(int j = i; j < vCount(); j++)   //j = i : 只判断单向边
                {
                    if(isAdjacent(i, j))
                    {
                        queue.add(Edge<E>(i, j, getEdge(i, j)));
                    }
                }
            }
            ret = toArray(queue);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "this function is for undirtected");
        }

        return ret;
    }

    SharePointer< Array<Edge<E>> > kruskal()
    {
        LinkQueue<Edge<E>> ret;
        DynamicArray<int> p(vCount());
        SharePointer<Array<Edge<E>>> edges = getUndiretedEdge();

        for(int i = 0; i < p.length(); i++)
            p[i] = -1;

        Sort::Shell(*edges);

        for(int j = 0; (j < edges->length()) && (ret.length() < (vCount()-1)); j++)
        {
            int b = find(p, (*edges)[j].b);
            int e = find(p, (*edges)[j].e);

            if(b != e)
            {
                ret.add((*edges)[j]);
                p[e] = b;
            }
        }

        if(ret.length() != (vCount() -1))
            THROW_EXCEPTION(InvalidOperationException, "no enough edges for kruskal");

        return toArray(ret);
    }

    SharePointer< Array<Edge<E>> > Prim(const E& LIMIT)
    {
        LinkQueue<Edge<E>> ret;

        if(asUndireted())
        {
            DynamicArray<bool> mark(vCount());      //记录搜索过的顶点
            DynamicArray<int> adjVex(vCount());     //记录路径
            DynamicArray<E> cost(vCount());         //记录权值
            SharePointer<Array<int>> aj = NULL;
            bool end =false;
            int v = 0;

            for(int j = 0; j < vCount(); j++)       //init
            {
                mark[j] = false;
                cost[j] = LIMIT;
                adjVex[j] = -1;
            }

            mark[v] = true;                         //add first element
            aj = getAdjacent(v);                    //get adjacent vertexs
            for(int i = 0; i < aj->length(); i++)
            {
                adjVex[(*aj)[i]] = v;               //添加到路径记录中
                cost[(*aj)[i]] = getEdge(v, (*aj)[i]);  //将权值记录到对应顶点
            }

            for(int j = 0; j < vCount(); j++)
            {
                E m = LIMIT;
                int k = -1;

                for(int i = 0; i < vCount(); i++)   //记录未检测的且权值最小的顶点
                {
                    if(!mark[i] && (cost[i] < m))
                    {
                        m = cost[i];
                        k = i;
                    }
                }

                end = (k == -1);

                if(!end)
                {
                    ret.add(Edge<E>(adjVex[k], k, getEdge(adjVex[k], k)));  //将获得的顶点记录到输出队列
                    mark[k] = true;     //标记检测状态

                    aj = getAdjacent(k);

                    for(int j = 0; j < aj->length(); j++)
                    {
                        if(!mark[(*aj)[j]] && (getEdge(k, (*aj)[j]) < cost[(*aj)[j]]))
                        {
                            cost[(*aj)[j]] = getEdge(k, (*aj)[j]);
                            adjVex[(*aj)[j]] = k;
                        }
                    }

                }
            }

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "prim is for undireted grap");
        }

        if(ret.length() != (vCount() - 1))
            THROW_EXCEPTION(InvalidOperationException, "No enough edge for prim");

        return toArray(ret);
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
