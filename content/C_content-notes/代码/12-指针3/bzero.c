/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-01 16:40:37
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-01 16:42:24
 * @FilePath: \CS22272\12指针3\code\bzero.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>
#include <string.h>


int main()
{
    int a = 5;

    bzero((void *)(&a),sizeof(a));  //bzero用来吧一段空间的内容，清0
    printf("%d\n",a);
}