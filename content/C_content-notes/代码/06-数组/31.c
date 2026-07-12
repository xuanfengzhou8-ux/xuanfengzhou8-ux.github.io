/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-22 15:14:35
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-22 15:22:05
 * @FilePath: \CS22272\06数组\code\31.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include<stdio.h>
#define N 8
int main ()
{
    int sum1[N]={0}; //大兔兔的数量
    int sum2[N]={1,1}; //小兔兔 
    
    int i,j;

    for (i=2;i<8;i++)
    {
      
        sum1[i]+=sum2[i-2];      //小兔变大兔兔 
        sum2[i]+=sum1[i-1];          //大兔兔生小兔
               
    }

    for (j=0;j<8;j++)
    {
        
        printf("%d ",sum1[j]+sum2[j]);
    }

    return 0;

}
