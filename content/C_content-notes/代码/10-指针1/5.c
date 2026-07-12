/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-28 09:06:59
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-28 09:42:43
 * @FilePath: \CS22272\10指针1\code\5.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

int main()
{
    int a=1;
    int *p = &a;
    p++;
    printf("&a=%p\n",&a);
    printf(" p=%p\n",p);

    double b;
    double *q=&b;
    q++;
    printf("&b=%p\n",&b);
    printf(" q=%p\n",q);

    //p ==> int *
    //*p ====> int 
    //printf("%d\n",*p);
}