#ifndef C_SORT_H
#define C_SORT_H

using namespace std;
namespace ZRBLib
{
void C_Swap(int* l, int* r)
{
    *l = *l + *r;
    *r = *l - *r;
    *l = *l - *r;
}

void C_Select(int* array, int len, bool min2max)
{
    int min = 0;

    for(int i = 0; i < len; i++)
    {
        min = i;
        for(int j = i+1; j < len; j++)
        {
            if(min2max ? (array[min] > array[j]) : (array[min] < array[j]))
                min = j;
        }
        if(min != i)
            C_Swap(&array[i], &array[min]);
    }
}

void C_Insert(int* array, int len, bool min2max)
{
    int tmp = 0;
    int pos = 0;
    for(int i = 1; i < len; i++)
    {
        tmp = array[i];
        pos = i;
        for(int j = i-1; j >= 0; j--)
        {
            if(min2max ? (tmp < array[j]) : (tmp > array[j]))
            {
                array[j+1] = array[j];
                pos = j;
            }
            else
            {
                break;
            }
            if(pos != i)
                array[pos] = tmp;
        }
    }
}

void C_Bouble(int* array, int len, bool min2max)
{
    int exchange = 1;

    for(int i = 0; (i < len) && exchange; i++)
    {
        exchange = 0;
        for(int j = len-1; j >= i; j--) //int j = 0; j < len-1-i; j++
        {
            if(min2max ? (array[j+1] < array[j]) : (array[j+1] > array[j]))
            {
                exchange = 1;
                C_Swap(&array[j+1], &array[j]);
            }
        }
    }
}

static void _C_Merge2(int* array, int* helper, int begin, int mid, int end, bool min2max)
{
    int i = begin, j = mid+1, k = begin;

    while((i <= mid) && (j <= end))
    {
        if(min2max ? (array[i] < array[j]) : (array[i] > array[j]))
            helper[k++] = array[i++];
        else
           helper[k++] = array[j++];
    }

    while(i <= mid)
        helper[k++] = array[i++];
    while(j <= end)
        helper[k++] = array[j++];

    for(i = begin; i <= end; i++)
    {
        array[i] = helper[i];
    }
}

static void _C_Merge(int* array, int* helper, int begin, int end, bool min2max)
{
    if(begin == end)
    {
        return;
    }
    else
    {
        int mid = (begin + end)/2;
        _C_Merge(array, helper, begin, mid, min2max);
        _C_Merge(array, helper, mid+1, end, min2max);
        _C_Merge2(array, helper, begin, mid, end, min2max);
    }
}

void C_Merge(int* array, int len, bool min2max)
{
    int helpper[len] = {0};

    _C_Merge(array, helpper, 0, len-1, min2max);

}

/*
 * 全排列
*/
void permutation(char* s, char* e)
{
    if(*s == '\0')
    {
        cout<< e<< endl;
    }
    else
    {
        int len = strlen(s);
        for(int i = 0; i < len; i++)
        {
            swap(s[0], s[i]);
            permutation(s+1, e);
            swap(s[0], s[i]);
        }
    }
}

void HanoTower(int n, char a, char b, char c)   //n 木块数量
{
    if(n == 1)
    {
        cout<< a << "-->"<< c<< endl;
    }
    else
    {
        HanoTower(n-1, a, c, b);    //将 n-1 个 a 借助 c 移动到b
        HanoTower(1, a, b, c);      //将最后一个 a 移动到 c
        HanoTower(n-1, b, a, c);    //将 b 借助 a 移动到 c
    }
}



}


#endif // C_SORT_H
