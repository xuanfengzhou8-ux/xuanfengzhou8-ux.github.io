/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-21 11:02:32
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-10 21:19:52
 * @FilePath: \CS22272\06数组\code\selectsort.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */






//简单选择排序


#include <stdio.h>


int main()
{
    int n =8 ;
    int a[8];
    int i =0;

    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        //printf("%d ",a[i]);
    }
    int min;
    for(i=0 ; i<n-1 ; i++)//遍历的次数
    {
        min = i;
        for(int j = i+1 ; j< n ; j++)
        {
            if(a[j] < a[min])
            {
                min = j;
            }
        }
        if(min !=i )
        {
            int temp;
            temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }

    for(i=0;i<8;i++)
    {
        
        printf("%d ",a[i]);
    }

}

