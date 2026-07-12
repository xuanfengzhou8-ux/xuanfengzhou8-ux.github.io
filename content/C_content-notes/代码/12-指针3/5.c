/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-01 11:24:03
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-01 11:39:18
 * @FilePath: \CS22272\12指针3\code\5.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */

#include <stdio.h>
#include <string.h>

int main()
{
    int m;
    m = strlen("anbcd");
    printf("%d\n",m);  //5
    char s[10]={"abc"};
    int l = strlen(s);
    printf("%d\n",l);//3

    printf("%ld\n",sizeof(s)); //10

    sizeof : 是一個运算符，用来求一个对象（或类型）所占的字节数！！！
    strlen : 是一个函数，用来求一个字符串的长度！！

    char s1[4] = {'1','0'};
    l = strlen(s1);
    l = 2;
    char s2[4] = {'1',0,'3'};
    l = strlen(s2);
    l = 1;
    l = strlen("abcd\123abc");
    l = 8;   //\123 

    l = strlen("abcd\089abcdefdfdfd");
    l = 4;    //匹配到\0

    l = strlen("ab\012abc");
    l = 6;

}