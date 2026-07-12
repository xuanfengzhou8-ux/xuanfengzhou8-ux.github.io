/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-26 09:14:10
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-26 09:30:33
 * @FilePath: \CS22272\08递归\code\1.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

int main()
{
   int a = 4267;
   while(a)
   {
        printf("%c",a%10+'0');
        a = a/10;
   }
   printf("\n");
   return 0;
}