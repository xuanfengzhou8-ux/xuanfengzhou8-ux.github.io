/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-26 16:22:34
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-26 16:24:50
 * @FilePath: \CS22272\09C程序组成\code\2.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

void point_a(void)
{
    static int a = 5;
    a++;
    printf("a=%d\n",a);
}


int main()
{
    point_a();  //6
    point_a();  //7
}