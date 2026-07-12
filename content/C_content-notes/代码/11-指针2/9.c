/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-29 14:19:09
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-29 15:14:44
 * @FilePath: \CS22272\11指针2\code\9.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // int n;
    // scanf();
    // int a[n];    //这是一个正常人的思维


    int b[4] ={1,2,3,4};

    int * p = (int *)malloc(sizeof(int)*4); 

    p[0] = 1;
    p[1] = 2;
    p[2] = 3;
    p[3] = 4;


    int i =0;
    for(i=0 ; i<4 ;i++)
    {
        printf("%d %d ",b[i],p[i]);
    }

    printf("\n");
}