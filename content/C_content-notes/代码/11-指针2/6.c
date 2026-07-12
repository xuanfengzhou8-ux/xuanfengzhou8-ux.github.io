/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-29 10:46:22
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-29 10:59:36
 * @FilePath: \CS22272\11指针2\code\6.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

// int [4] b[] , int n   ===>  int b[][4] , int n

// int find_max_v2(int b[][4] , int n)
// {
//     int i ,j;
//     int max = a[0][0];
//     for()
//     {
//         fot()
//         {
//             if()
//             {
//                 max =b[i][j]
//             }
//         }
//     }
// }


int find_max_v2(int (*b)[4], int n )
{
    // b = a;
    // b = &a[0];
    // a[i][j] <===> *&a[i][j]  =====> *(a[i]+j) ===>*(*(a+i)+j)  ===== *(&a[i][0]+j)
    
    // a[i][j]  =====  *(*(a+i)+j)
    
    // *(*(&a[0]+i)+j) ==== *(*(b+i)+j) ===== *(b[i]+j)  ===== b[i][j]

    int i ,j;
    int max = b[0][0];
    for(i=0;i<n;i++)
    {
        for(j=0;j<4;j++)
        {
            // if(b[i][j]>max)
            // {
            //     max =b[i][j];
            // }
            if(*(*(b+i)+j)>max)
            {
                max =*(*(b+i)+j);
            }
        }
    }
    return max;
}


int main()
{
    int a[3][4]={1,2,33,66,77};
    int max = find_max_v2(a,3);
    printf("%d\n",max);
    // b = a ;
    // b =&a[0];
    // typeof(&a[0]):typeof(a[0]) * =====> int[4] *
    // int b[][4]  =====> int [4] *b =====>int (*b)[4]
    // n=3;

}
