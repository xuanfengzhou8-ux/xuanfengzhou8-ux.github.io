/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-21 09:18:49
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-21 09:25:47
 * @FilePath: \CS22272\06数组\code\zouye2.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
// 求斐波那契数列(Fibonacci)前20项之和
// 	斐波那契数列： 1 1 2 3 5 8 13 ，……。

// int a =1 ;
// int b =1 ;
// int c =a + b;
// int d = c + b;
// int e = d + c;
// ......
// int a[20];
// a[0]=1;
// a[1]=1;
// a[2]=a[0]+a[1];
// a[3]=a[2]+a[1];
// ........重复

// a[0]=1;
// a[1]=1;
// int sum = 2;
// 循环
// for(int i = 2 ;i < 20 ;i++)
// {
//     a[i] = a[i-1]+a[i-2];
//     sum = sum + a[i];
// }

#include <stdio.h>

int main()
{
     int a[20] = {1,1};
     int i,s,sum = 2;
     
     for ( i = 0; i < 18; i++)//i最大为17
     {
          a[i+2] = a[i] + a[i+1];

          sum  = sum + a[i+2]; //加到a[19]
     }
     printf("%d\n",sum);
     
}
