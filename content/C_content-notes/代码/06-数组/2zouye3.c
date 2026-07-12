/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-22 09:45:04
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-22 10:05:27
 * @FilePath: \CS22272\06数组\code\2zouye3.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>
//my code
int main() 
{
   int a[3][3] = {1,2,3,4,5,6,7,8,9};
   int b[5][5] = {0};
   int c = 0;
   int i,j;
   for(i=0;i<3 ;i++)
   {
        for(j=0;j<3;j++)
        {
            b[i+1][j+1] = a[i][j];
        }
   }
    for(i=0;i<5 ;i++)
   {
        for(j=0;j<5;j++)
        {
           printf("%d ",b[i][j]);
        }
        printf("\n");
   }
   for(i=0;i<3;i++)
   {
        for(j=0;j<3;j++)
        {
            if((i==0||a[i][j]>a[i-1][j])&&(i==2||a[i][j]>a[i+1][j])&&(j==0||a[i][j]>a[i][j-1])&&(j==2||a[i][j]>a[i][j+1]))
            {
                c++;
            }
        }
   }

   printf("山顶有:%d个\n",c);
   return 0;


}

