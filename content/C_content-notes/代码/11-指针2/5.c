/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-29 10:18:53
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-29 10:22:04
 * @FilePath: \CS22272\11指针2\code\5.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>


int find_max(int *b , int n)
{
    // b  &a[0]
    // b + i ==> &a[0]+i ==> &a[i]
    // *(b+i) ===> * & a[i] ===> a[i]

    int i;
    int max = b[0];

    for(i=0;i<n;i++)
    {
        if(b[i]>max)
        {
            max = b[i];
        }
        // if(*(b+i) > max)
        // {
        //     max = *(b+i);
        // }
    }
    return max;
}


int main()
{
    int a[5]={5,9,6,78,1};

    int max = find_max(a,5);

    printf("%d\n",max);

    return 1;
}