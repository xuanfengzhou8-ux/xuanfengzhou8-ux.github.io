/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-28 09:45:41
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-28 10:04:58
 * @FilePath: \CS22272\10指针1\code\6.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

int main()
{
    int a[10];
        //数组的元素的地址是连续！！！
    
    int *p ;
    p = &a[0];
    printf("    p = %p\n" , p);  
    p = a;
    printf("    p = %p\n" , p);  
    // printf("    a = %p\n" , a);  
    // printf("&a[9] = %p\n",&a[9]);      
}

