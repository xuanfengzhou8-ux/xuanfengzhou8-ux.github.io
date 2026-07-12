/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-03 15:20:17
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-03 15:21:47
 * @FilePath: \CS22272\14共用体\code\dx.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>
union test
{
    int a;
    char b;
};



int main()
{
    union test t;
    t.a = 1 ; //0x00000001

    if(t.b)
    {
        //小端
        printf("xiaoduan\n");
    }
    else
    {
        //大端
        printf("daduan\n");
    }
}