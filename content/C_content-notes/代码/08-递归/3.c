/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-26 14:57:25
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-26 15:15:53
 * @FilePath: \CS22272\08递归\code\3.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
//#include <stdio.h>

//确定任务目标（起名字），确定任务输入参数（参数），确定返回值，具体实现代码

/**
 * @description:    判斷一個一维数组是否递增
 * @param {int} a ： 数组名
 * @param {int} n ：数组元素个数
 * @return {*}
    0 表示非递增
    1 表示递增
 */
// int is_ascend(int a[],int n)
// {
//     if(n<2)
//     {
//         return 1;
//     }
//     else
//     {
//         return is_ascend(a,n-1) && a[n-1] > a[n-2];
//     }

// }

// int main()
// {
    
//     return 1;
// }


#include<stdio.h>
#include<stdlib.h>

int PD(int a[],int n)//递归判断一维数组是否递增
{	
	int f=1;
	if(n==0)
	{
		a[n]=a[0];
	}
	else
	{
		if(a[n]>=a[n-1])
		{
			f=PD(a,n-1);
		}
		else
		{
			f=0;
            return f;
		}
	}
	
	return f;
	
}

int main()
{
	int a[5]={1,25,3,4,5};
	int s=PD(a,4);
	if(s==0)
	{
		printf("不递增\n");
	}
	else
	{
		 printf("递增\n");
	}
}