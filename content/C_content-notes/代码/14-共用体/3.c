/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-03 14:38:05
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-03 14:38:23
 * @FilePath: \CS22272\14共用体\code\3.c
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
    t.a = 0x11223344;
    printf("%c\n",t.b);

}
