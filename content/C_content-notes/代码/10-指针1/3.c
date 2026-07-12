/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-27 16:22:53
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-27 16:29:08
 * @FilePath: \CS22272\10指针1\code\3.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */

#include <stdio.h>


int main()
{
    int a =5;
    int b;

            //定义p
            //根据上下文，p保存 &a ， p指向a
            //p是一个指针，并且p指向的类型是 typeof（a）
    int *p;
    p = &a;
    //*p = *&a = a;
    *p = 1024;
    printf("a=%d\n",a);

    b = *p;
    printf("b=%d\n",b);
    return 0;

}