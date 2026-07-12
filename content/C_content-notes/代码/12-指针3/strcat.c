/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-01 16:42:51
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-01 16:45:11
 * @FilePath: \CS22272\12指针3\code\strcat.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>
#include <string.h>

int main()
{
    char s1[8]= {"abc"};
    //strcat(s1 , "12345678");  //已经越界
    strncat(s1 , "123456", 3);
    printf("%s\n",s1);
}