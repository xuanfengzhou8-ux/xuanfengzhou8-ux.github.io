/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-29 09:07:30
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-30 16:49:37
 * @FilePath: \CS22272\11指针2\code\1.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>
void swap(int a,int b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
    printf("a=%d\n",a);
    printf("b=%d\n",b);
}

int main()
{
    int a =100;
    int b =200;
    swap(a,b);
    printf("a=%d\n",a);
    printf("b=%d\n",b);
}