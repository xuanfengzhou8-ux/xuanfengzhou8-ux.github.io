/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-20 15:04:06
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-20 15:10:30
 * @FilePath: \CS22272\06数组\code\4.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
//不用排序，把一个一维数组中负数放在数组的前面！！！


#include <stdio.h>

int main()
{
    int a[7]={1,-2,3,4,6,-9,-2};
    int i;
    int j;
    for(i = 0 ,j = 6 ;  i < j ;   )
    {
        while(a[i] < 0)
        {
            i++;
        }
        while(a[j] >=0)
        {
                j--;
        } 
        if( i < j )
        {
                int temp ;
                temp = a[i];
                a[i] = a[j];
                a[j]=temp;
        }
    }

    for(int k = 0 ; k<7 ; k++)
    {
    printf("%d ",a[k]);

    }
    printf("\n");
    return 0;

}






