/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-21 14:59:43
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-21 15:06:20
 * @FilePath: \CS22272\06数组\code\21.C
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */


// 定义一个二维数组，从键盘上按行输入每个元素的值！！

// int a[3][4];
// scanf("%d",&a[0][0]);
// scanf("%d",&a[0][1]);
// scanf("%d",&a[0][2]);
// scanf("%d",&a[0][3]);

// j 列数  0，1，2，3

// scanf("%d",&a[0][j])
// j++

// ==>
//     for(j = 0 ; j < 4 ; j++)
//     {
//         scanf("%d",&a[0][j]);
//     }
//     for(j = 0 ; j < 4 ; j++)
//     {
//         scanf("%d",&a[1][j]);
//     }
//     for(j = 0 ; j < 4 ; j++)
//     {
//         scanf("%d",&a[2][j]);
//     }

// i 行数  0，1，2
// for(i=0;i<3;i++)
// {
//     for(j=0 ; j<4 ;j++)
//     {
//         scanf("%d",&a[i][j]);
//     }
// }
#include <stdio.h>
int main()
{
    int a[3][4]={0};
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0 ; j<4 ;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }

    
    for(i=0;i<3;i++)
    {
        for(j=0 ; j<4 ;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}