/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-27 15:07:23
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-27 15:13:10
 * @FilePath: \CS22272\10指针1\code\2.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */

#include <stdio.h>


int main()
{
    int a =5 ; 
    int b;

    //a =1024;
    *&a = 1024;

    b = a;
     
    b = *&a;

    printf("a=%d\n",a);
    printf("b=%d\n",b);



    printf("&a = %p\n" , &a);
    printf("&*&a = %p\n", &*&a);
    printf("*&*&*&a = %d\n",*&*&*&a);

}