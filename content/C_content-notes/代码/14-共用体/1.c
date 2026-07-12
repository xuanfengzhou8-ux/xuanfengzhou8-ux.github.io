/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-03 14:30:14
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-03 14:34:40
 * @FilePath: \CS22272\14共用体\code\1.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */

struct test
{
    int a;
    int b[4];
};


union ttt
{
    char c;
    struct test t1;
};

sizeof(union ttt) = 20 

union test
{
    char a;
    char b;
};

union test t;
t.a = 'A';
printf("%c\n",t.b);


union test 
{
    int a;
    char b;
};
union test t;
t.a = 0x11223344;
printf("%c\n",t.b);