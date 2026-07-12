/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-28 09:59:48
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-28 10:18:55
 * @FilePath: \CS22272\10指针1\code\7.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>


int main()
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};

    //a+1; // 在这个表达式中，a当作指针来用
        //&a[0]+1 == &a[1];

    //a+i; //&a[0]+i == &a[i]

    //.....

    //*(a+i) ==> *(&a[0]+i)====>*(&a[i])=====>a[i];

    printf("%d\n",*(a+2));

}