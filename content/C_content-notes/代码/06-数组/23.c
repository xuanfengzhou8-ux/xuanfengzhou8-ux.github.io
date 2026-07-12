/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-21 16:54:39
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-21 16:57:06
 * @FilePath: \CS22272\06数组\code\23.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

#define N 3
#define M 4

int main()
{
    int a[N][M];
    int i ,j ;
    for(i=0;i<3;i++)
    {
        for(j=0 ; j<4 ;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }

    int b[M][N];
    for(i=0;i<N;i++)
    {
        for(j = 0 ; j<M ; j++)
        {
            b[j][i] = a[i][j];
        }
    }

    for(i=0;i<M;i++)
    {
        for(j = 0 ; j<N ; j++)
        {
           printf("%d ",b[i][j]);
        }
        printf("\n");
    }
    

}