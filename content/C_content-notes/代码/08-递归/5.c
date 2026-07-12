/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-26 15:16:42
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-26 15:19:38
 * @FilePath: \CS22272\08递归\code\5.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>
int up(int a[],int n)
{
    if (n==0)
    {
        return 0;
    }
    else
    {
        if(a[n-1]>up(a,n-1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
int main()
{
    int a[5]={1,2,5,4,5};
    int num = up(a,5);
    if(num == 1)
    {
        printf("up\n");

    }
    else
    {
        printf("no\n");
    }
}