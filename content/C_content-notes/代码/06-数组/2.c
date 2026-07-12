/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-20 11:31:06
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-20 13:50:57
 * @FilePath: \CS22272\06数组\code\2.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */

#include <stdio.h>

int main()
{
    int a[5];
    int i =0;

    for(i=0;i<4;i++)
    {
        scanf("%d",&a[i]);
        //printf("%d ",a[i]);
    }

    //find max

    int max = a[0];

    for(i=0;i<4;i++)
    {
        if(max < a[i])
        {
            max = a[i];
        }
    }

    //find min
    int min= a[0];
    for(i=0;i<4;i++)
    {
        if(min > a[i])
        {
            min = a[i];
        }
    }

    //num 保存max + min
    int num = max + min ;
    printf("最大值加最小值 = %d \n",num);


    //求和 sum 

    int sum = 0;
    for(i=0;i<4;i++)
    {
        sum += a[i];
    }
    printf("sum = %d\n", sum);
}