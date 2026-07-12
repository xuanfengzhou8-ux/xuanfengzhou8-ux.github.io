/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-01 10:03:44
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-01 11:23:44
 * @FilePath: \CS22272\12指针3\code\3.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */




char s1[]={'a','b','c'};
char s2[]={"abc"};  ======> char s2[]={'a','b','c','\0'};
    NOTE: "abc" ==>abc\0
        编译器只会在    字符串常量（“”引起来）后面加个0；

    请问  s1的元素个数是多少？  3
         s2的元素个数是多少？   4
         sizeof(s1)   求s1所占的字节数
         sizeof(数组) = sizeof(数组元素) * 元素个数

         sizeof(s1) = sizeof(char) * n = n;

char s3[5]={'a','b','b'};       //5
char s4[5]={"abc"};     //5

    sizeof(s3) = 5;
    sizeof(s4) = 5;

char s5[5]={"abcde"};  //error ,why;



NAME
       strlen - calculate the length of a string
                计算一个字符串的长度

SYNOPSIS
       #include <string.h>
        头文件

       size_t strlen(const char *s);
        函数原型：
        返回值：    
            返回长度 ， int

DESCRIPTION
       The strlen() function calculates the length of the string pointed to by
       s, excluding the terminating null byte ('\0').

RETURN VALUE
       The strlen() function returns the number of characters  in  the  string
       pointed to by s.

例子：
    int l ;
    l = strlen("abcde");  
    l=5?6
    -----
    char s[10] = {"abc"};
    l = strlen(s);
    l = 3;
