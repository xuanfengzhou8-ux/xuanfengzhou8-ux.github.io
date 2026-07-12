/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-21 09:02:42
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-21 09:17:38
 * @FilePath: \CS22272\06数组\code\zouye1.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
// 找出一个数组中第二大的数，不用排序；

#include <stdio.h>


int main()
{
	int a;
	printf("输入数组个数：\n");
	scanf("%d",&a);
	int i;
	int num[a];
	printf("赋值：\n");
	for(i = 0;i < a;i++)
	{
		scanf("%d",&num[i]);
	}


    int max=num[0],max1=num[0];
    for ( i = 0; i < a; i++)
    {
        if(num[i]>max)
        {
            max1=max;
            max=num[i];
        }
        else 
        {
            if(max1<num[i])
            {
                max1=num[i];
            }
        }
    }
    printf("第二大的数：%d\n",max1);
}


