/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-25 16:00:58
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-25 16:07:31
 * @FilePath: \CS22272\07函数\code\3.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

//int gao_data(int a[][4],int n,int k);
int gao_data(int [][4],int ,int );

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
    printf("please input need : \n");
    int k;
    scanf("%d",&k);

    int c = gao_data(a,3,k);
    printf("%d\n",c);

}



int gao_data(int a[][4],int n,int k)
{
    int b=0;   //用来保存有多少种坐的方式！！
    int c = 0;   //这个c是我用来计数！！
    int sum = 0;  //求和！！
    int i,j;
    for(i = 0 ; i < 3 ; i++)
    {
        c = 0 ;
        for(j=0 ; j<4 ; j++)
        {
            sum = sum + a[i][j];
            if(sum == 0)
            {
                c++;   //一个为0.则记一个位置！！
            }
            else if(sum == 1)   //出现1 ，重新记数
            {
                sum = 0;    //对sum重新赋值
                c = 0;      //此时，我们的计数器也需要重新赋值
            }
            if(c>=k)
            {
                b++;
            }
        }
    }
    if(b == 0)
    {
        printf("高数巨逃课，寄了\n");
    }
    return b;
}