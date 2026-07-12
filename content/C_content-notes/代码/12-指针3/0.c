/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-01 09:11:02
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-01 09:15:38
 * @FilePath: \CS22272\12指针3\code\0.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

int main()
{
    int i ;
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    int sum=0;

    int *p[10];

    for(i=0; i <10 ; i++)
    {
        p[i] = &a[i];
    }
    int **pp;    //定义一个变量pp
    pp = p;
    //通过pp的表达式。求数组a的和
    for(i = 0 ; i< 10; i++)
    {
        sum +=*(*pp + i);
    }
    printf("%d\n",sum);
    return 0;
}