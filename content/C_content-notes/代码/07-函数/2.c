/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-25 15:55:35
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-25 15:59:57
 * @FilePath: \CS22272\07函数\code\2.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>


/**
 * @description:     判断数组是否递增
 * @param {int []} a 
 * @param {int} n
 * @return {*}
    返回一个int类型的值
 */
int puanduan(int a[] , int n)   
{
    int flag = 1 ;  //假定当flag==1的时候，则说明数组递增，反之则，递减
    for(int i = 0 ; i < n ; i++)
    {
        if(a[i] > a[i+1])
        {
            flag = 0;
            break;
        }
    }
    return flag;
}

int main()
{
    int a[8]={1,2,3,4,5,6,7,8};

    int n = -1 ; 

    n = puanduan(a,8);

    if(n==1)
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }

    return 0;
}