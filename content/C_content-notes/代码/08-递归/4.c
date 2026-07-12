#include <stdio.h>

//写一个函数求一个一维数组的最大值！

int find_max(int a[] , int n)
{
    if(n==1)
    {
        return a[0];
    }
    else
    {
        int f = find_max(a,n-1);
        return f > a[n-1]? f : a[n-1];
    }
}

int main()
{
    int a[5]={2,67,9,3,55};
    int max = find_max(a,5);
    printf("%d\n",max);
}