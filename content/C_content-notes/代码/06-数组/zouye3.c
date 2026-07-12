/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-21 09:26:13
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-21 09:31:19
 * @FilePath: \CS22272\06数组\code\zouye3.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
// 在一个升序排序的数组中，查找一个元素x，如果找到了。返回其下表，没有找到返回-1



// 2 3 4 5 6 7     find 6
// int num=-1;
// for(i=0;i<n;i++)
// {
//     if(a[i]==x)
//     {
//         num = i;
//         break;
//     }
// }


#include<stdio.h>
int main()
{
    int a[6],i,x;
    for(i=0;i<6;i++)
    {
        scanf("%d",&a[i]);
    }

    printf("输入：");
    scanf("%d",&x);
    for(i=0;i<6;i++)
    {
        if(a[i]==x)
        {
            
            printf("该数下标为：%d\n",i);
            return i;
        }
    }
    printf("no\n");
    return -1;

  
}  