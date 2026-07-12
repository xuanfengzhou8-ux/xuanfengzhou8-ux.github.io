/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-21 11:39:21
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-21 11:45:17
 * @FilePath: \CS22272\06数组\code\test.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include<stdio.h>
int main()
{
    int x;
    int a[10] = {1,2,6,8,9,10,14,15,16,17};
    int flog = 0;
    scanf("%d",&x);
    for(int i=0;i<10;i++)
    {
        if(x == a[i])
        {
            printf("找到了,其下标为%d\n",i);
            flog=1;
            break;
        }
    }

    if(flog == 0)
    {
        printf("-1\n");
    }
    
}