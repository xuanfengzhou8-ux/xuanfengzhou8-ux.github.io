/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-01 09:35:35
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-01 09:44:20
 * @FilePath: \CS22272\12指针3\code\2.c
 * @Description: 

 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */

#include <stdio.h>


int main()
{
    char s[5] =  {'a','b','c'};

    char *p = s;

        //p保存的是&s[0],'a'的地址
        //*p代表它指向的對象.s[0],有左值， 右值

    //数组s是一个可读可写的，“abc”是字符串常量
    char s[5] = {"abc"};
    ===>
        s[0] = 'a';
        s[1] = 'b';
        s[2] = 'c';
        s[3] = '\0';
        s[4] = 0;
    
    char *p = s;
    int i ;

    // p保存的s[0]地址，*p表示s[0],是一个变量
    *p = 'A';

    for(i=0; *(p+i) != 0;i++)
    {
        printf("%c\n",*(p+i));
    }
    return 0;
    
}