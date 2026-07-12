/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-22 10:07:46
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-22 10:13:12
 * @FilePath: \CS22272\06数组\code\2zouye2.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

#define N 10

int main()
{
    int i,j;
    int a[N][N] = {0};

    for(i=0;i<N;i++)
    {
        a[i][i] = 1;
        a[i][0] = 1;
        for(j=1;j<i;j++)
        {
            a[i][j] = a[i-1][j-1]+a[i-1][j];
        }
    }
    for(i=0;i<N ;i++)
   {
        for(j=0;j<=i;j++)
        {
           printf("%d ",a[i][j]);
        }
        printf("\n");
   }
}