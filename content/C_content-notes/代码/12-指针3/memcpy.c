/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-01 16:37:36
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-01 16:39:52
 * @FilePath: \CS22272\12指针3\code\memcpy.C
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>
#include <string.h>

int main()
{
    char s1[8];
    char s2[8] ={"abcd"};

    printf("%p\n",s1);
    printf("%p\n",s2);

    memcpy(s1,"123\0abcd",8);

    printf("%s\n",s1);
    printf("%s\n",s2);

}