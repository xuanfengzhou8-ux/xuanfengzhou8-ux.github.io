/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-21 10:10:34
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-11 20:50:16
 * @FilePath: \CS22272\06数组\code\maopao.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */



#include <stdio.h>


//冒泡排序
int main()
{
    int n =8 ;
    int a[8];
    int i =0;

    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        //printf("%d ",a[i]);
    }


    for(i = 0 ; i < n-1 ; i++)
    {
        int flag = 0;
        for(int j = n -1; j > i ; j--)
        {
        
            if(a[j-1] > a[j])
            {
                int temp;
                temp = a[j-1];
                a[j-1] = a[j];
                a[j] = temp;
                flag = 1;
            }
        }
        if(flag == 0)
        {
            for(i=0;i<8;i++)
            {
                
                printf("%d ",a[i]);
            }
            printf("\n");
            printf("你提前完成工作。你牛逼！！\n");
            
            return 1;
        }
    }

    return 0;
}





