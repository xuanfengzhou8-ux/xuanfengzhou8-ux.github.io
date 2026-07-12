/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-29 14:14:27
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-29 14:17:00
 * @FilePath: \CS22272\11指针2\code\8.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>


int array_sum(int a[],int n)
{
    int sum = 0;
    for(int i =0 ; i <n; i++)
    {
        sum += a[i];
    }
    return sum;
}


int main()
{
    int a[5]={1,2,3,4,5};

    //定义一个指针变量p ，来保存函数array_sum的地址

    int (*p)(int a[],int n);

    p = array_sum;
    //p = &array_sum;

    printf("%d\n",p(a,5));
}