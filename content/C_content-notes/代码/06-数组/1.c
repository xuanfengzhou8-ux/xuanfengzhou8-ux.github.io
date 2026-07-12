#include <stdio.h>


//1、定义一个一维数组，并通过键盘来一一对每个元素赋值
int main()
{
    int a[5];
    int i =0;

    for(i=0;i<5;i++)
    {
        scanf("%d",&a[i]);
        //printf("%d ",a[i]);
    }

    for(i=0;i<6;i++)
    {
        
        printf("%d ",a[i]);
    }

    return 0;
}