/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-28 16:19:38
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-28 17:17:19
 * @FilePath: \CS22272\10指针1\code\Quick.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

void Qsort(int a[], int low , int high);
int Partition(int a[] , int low, int high);
void QucikSort(int a[],int n);



void QucikSort(int a[],int n)
{
    Qsort(a,0,n-1);
}

//对数组的子数组[low - high]进行快速排序
void Qsort(int a[], int low , int high)
{
    int pivot;
    if(low<high)
    {
        pivot = Partition(a,low,high);   // 讲数组 low-high 一分为二  
                                        //算出枢轴值pivot
            //第一次排序之后，我们的low变成了5，然后整个数组变成了a[10]= {20,10,40,30,50,70,80,60,90}
        Qsort(a,low,pivot-1);       // 对低子表递归排序
        //把{20,10,40,30}；进行排序
        Qsort(a,pivot+1,high);        //对高子表递归排序
        //把{70，80，60，90}；进行排序
    }
}

int Partition(int a[] , int low, int high)
{
    int pivotkey;
    pivotkey = a[low];
    while(low < high)
    {
        while(low < high && a[high] >= pivotkey)
        {
            high--;
        }
        int temp ;
        temp = a[low];
        a[low] = a[high];
        a[high] = temp;
        while(low < high && a[low] <= pivotkey)
        {
            low++;
        }
        temp = a[low];
        a[low] = a[high];
        a[high] = temp;   //交换
    }
    return low;
}


int main()
{
    int a[10]={5,4,6,2,1,7,9,3,8,10};
    QucikSort(a,10);
    for(int i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}   