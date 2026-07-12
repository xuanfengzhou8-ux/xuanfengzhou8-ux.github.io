/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-27 14:58:00
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-27 15:03:01
 * @FilePath: \CS22272\10指针1\code\1.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>


int main()
{
    int a;

    scanf("%d",&a);

    //printf("%d\n",a);
    printf("%p\n",&a);  // 按地址的形式（16进制输出）如果我们机器是32bits，输出32bits的16进制     如果机器是64bit ， 那么输出就是64bits的16进制

    printf("%u\n",&a);  //按照十进制输出，  unsigned int 
    printf("%x\n",&a);
    
}