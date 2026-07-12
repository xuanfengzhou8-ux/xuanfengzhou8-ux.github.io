/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-26 14:00:30
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-26 14:09:05
 * @FilePath: \CS22272\08递归\code\2.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

//确定任务目标（起名字），确定任务输入参数（参数），确定返回值，具体实现代码
int array_sum(int a[],int n)
{
    if(n == 0)
    {
        return 0;
    }
    else
    {
        return array_sum(a,n-1)+a[n-1];
    }
}

int main()
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    int sum=0;
    sum = array_sum(a,10);
    printf("%d\n",sum);
    return 0;
}