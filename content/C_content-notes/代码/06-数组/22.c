/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-21 15:23:32
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-21 15:27:42
 * @FilePath: \CS22272\06数组\code\22.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
// 遍历二维数组，求该二位数组中元素的最大值，最小值以及所有元素的和！！



#include <stdio.h>

#define N 3
#define M 4

int main()
{
    int a[N][M];
    int i ,j ;
    int max;
    int min;
    int sum =0 ;

    for(i=0;i<3;i++)
    {
        for(j=0 ; j<4 ;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }

    max = a[0][0];
    min = a[0][0];

    for(i=0;i<3;i++)
    {
        for(j=0 ; j<4 ;j++)
        {
            if(a[i][j] > max)
            {
                max = a[i][j];
            }
            if(a[i][j] < min)
            {
                min = a[i][j];
            }
            sum = sum + a[i][j];
        }
        
    }

    printf("max = %d,min = %d,sum = %d\n",max,min,sum);
    return 0;
}