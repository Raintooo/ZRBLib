﻿#ifndef SORT_H
#define SORT_H

#include "Object.h"

namespace ZRBLib
{

class Sort : public Object
{
private:
    Sort();
    Sort(const Sort& e);
    Sort& operator = (const Sort& e);

    template <typename T>
    static void Swap(T& a, T& b);

    template <typename T>
    static void Merge(T src[], T helper[], int begin, int mid, int end, bool min2max = true);

    template <typename T>
    static void Merge(T src[], T helper[], int begin, int end, bool min2max = true);

public:
    template <typename T>
    static void Select(T array[], int len, bool min2max = true);

    template <typename T>
    static void Insert(T array[], int len, bool min2max = true);

    template <typename T>
    static void Bouble(T array[], int len, bool min2max = true);

    template <typename T>
    static void Shell(T array[], int len, bool min2max = true);

    template <typename T>
    static void Merge(T array[], int len, bool min2max = true);

};

template <typename T>
void Sort::Swap(T& a, T& b)
{
    T t(a);
    a = b;
    b = t;
}

template <typename T>
void Sort::Select(T array[], int len, bool min2max)
{
    int min;
    for(int i = 0; i < len; i++)
    {
        min = i;
        for(int j = i+1; j < len; j++)
        {
            if(min2max ? (array[i] > array[j]) : (array[i] < array[j])) //(min2max && (array[i] > array[j])) || (!min2max && (array[i] < array[j]))
            {
                min = j;
            }
        }
        if(min != i)
            Swap(array[min], array[i]);
    }
}

template <typename T>
void Sort::Insert(T array[], int len, bool min2max)
{
    for(int i = 1; i < len; i++)
    {
        int m = i;
        T tmp = array[i];
        for(int j = i-1; j >= 0; j--)
        {
            if(min2max ? (array[j] > tmp) : (array[j] < tmp))
            {
                array[j+1] = array[j];
                m = j;
            }
            else
            {
                break;
            }
        }
        if(m != i)
            array[m] = tmp;
    }
}

template <typename T>
void Sort::Bouble(T array[], int len, bool min2max)
{
    bool exchange = true;

    for(int i = 0; (i < len) && exchange; i++)
    {
        exchange = false;
        for(int j = len-1; j > i; j--)
        {
            if(min2max ? (array[j] < array[j-1]) : (array[j] > array[j-1]))
            {
                Swap(array[j-1], array[j]);
                exchange = true;
            }
        }
    }
}

template <typename T>
void Sort::Shell(T array[], int len, bool min2max)
{
    int d = len;

    do
    {
        d = d/3 + 1;
        for(int i = d; i < len; i+=d)
        {
            int m = i;
            T tmp = array[i];
            for(int j = i-d; j >= 0; j-=d)
            {
                if(min2max ? (array[j] > tmp) : (array[j] < tmp))
                {
                    array[j+d] = array[j];
                    m = j;
                }
                else
                {
                    break;
                }
            }
            if(m != i)
                array[m] = tmp;
        }

    }while(d > 1);
}

template <typename T>
void Sort::Merge(T array[], int len, bool min2max)
{
    T* helper = new T[len];

    if(helper != NULL)
        Merge(array, helper, 0, len-1, min2max);

    delete helper;
}

template <typename T>
void Sort::Merge(T src[], T helper[], int begin, int mid, int end, bool min2max)
{
    int i = begin, j = mid+1, k = begin;

    while((i <= mid) && (j <= end))
    {
       if(min2max ? (src[i] < src[j]) : (src[i] > src[j]))
            helper[k++] = src[i++];
       else
            helper[k++] = src[j++];
    }

    while(i <= mid)
        helper[k++] = src[i++];
    while(j <= end)
        helper[k++] = src[j++];

    /*
     * 将排好序的数组拷贝回 src 是因为返回上一层递归后再利用 src 合并
    */
    for(i = begin; i <= end; i++)
    {
        src[i] = helper[i];
    }
}

template <typename T>
void Sort::Merge(T src[], T helper[], int begin, int end, bool min2max)
{
    if(begin == end)
    {
        return;
    }
    else
    {
        int mid = (begin + end)/2;
        Merge(src, helper, begin, mid, min2max);
        Merge(src, helper, mid+1, end, min2max);
        Merge(src, helper, begin, mid, end, min2max);
    }

}


}


#endif // SORT_H