/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-29 10:01:48
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-29 10:06:31
 * @FilePath: \CS22272\11指针2\code\4.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>




int find_max(int b[],int n)
{

}

int main()
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    find_max(a,10);
        //函数调用
            形参 = 实参的值
            b = a ;
            n = 10;
        //此处a，b数组名：当成指针在用
            b = a ;
            b = &a[0];

            typeof(&a[0]) : typeof(a[0]) * ====> int *
            typeof(b) : int *

    find_max(int b[],int n)
    find_max(int *b , int n)   //b n 形参 
    {

    }

}