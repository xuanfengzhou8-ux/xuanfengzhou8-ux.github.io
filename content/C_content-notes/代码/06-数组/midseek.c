/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-05 11:09:14
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-05 11:15:36
 * @FilePath: \CS22272\06数组\code\midseek.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

int search(int num[] ,int size ,int target)
{
    int left = 0;
    int right = size-1;

    while(left <= right)
    {
        int middle = (left + right )/2;

        if(num[middle] > target)
        {
            right  = middle - 1;
        }
        else if(num[middle] < target)
        {
            left = middle + 1;
        }
        else
        {
            return middle;
        }
        
    }
    return -1;
}


int main()
{
    int a[5]={4,6,8,33,99};

    int falg = search(a,5,33);

    printf("falg = %d\n" ,falg);
}