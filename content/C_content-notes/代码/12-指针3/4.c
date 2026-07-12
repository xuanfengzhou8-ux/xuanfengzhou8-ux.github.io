/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-01 10:18:44
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-01 11:18:21
 * @FilePath: \CS22272\12指针3\code\4.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>
#include <string.h>


int strlen_m(char *s)
{
    int n = 0;
    while(*s)
    {
        n++;
        s++;
    }
    return n;
}
int main()
{
    char *s = "abncde";

    int sum = strlen_m(s);

    printf("%d\n",sum);
}
