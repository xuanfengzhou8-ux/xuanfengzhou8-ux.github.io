/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-03 14:32:58
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-03 14:33:31
 * @FilePath: \CS22272\14共用体\code\2.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>



union test
{
    char a;
    char b;
};
int main()
{
    union test t;
    t.a = 'A';
    printf("%c\n",t.b);

}
