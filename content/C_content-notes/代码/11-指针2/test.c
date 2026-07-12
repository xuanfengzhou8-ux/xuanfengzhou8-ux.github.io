/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-29 11:03:18
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-29 11:04:34
 * @FilePath: \CS22272\11指针2\code\test.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>


int main()
{
    int a=10;
    printf("%d\n",a);

    while(1)
    {
        int i =10;
        i--;
        printf("%d\n",i);
        if(i==0)
        {
            break;
        }
    }
    printf("%d\n",i);
}