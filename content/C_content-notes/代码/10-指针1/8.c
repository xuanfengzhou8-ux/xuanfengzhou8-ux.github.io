/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-28 14:54:38
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-28 19:55:20
 * @FilePath: \CS22272\10指针1\code\8.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

int main()
{
    // int *p[4];       //定义了一个数组，名字叫p，里面放了4个指针类型的元素

    // int a[10] = {1,2,3,4,5,6,7,8,9,10};

    // p[0] = &a[6];

    // printf("%d\n",*p[0]);  //7


    // int a[4]= {1,2,3,4};
    // int *p[4]; //指针数组
    // for(int i= 0 ; i<4;i++)
    // {
    //     p[i] = a+i;  //*p[0] = *&a[0] = a[0]
    // }

    // for(int i = 0 ;i<4 ; i++)
    // {
    //     printf("%d ",*p[i]);
    // }
    // printf("\n");
//     int a[4]= {1,2,3,4};
//     int (*p)[4];  //数组指针 ，指向一个int[4]类型的数组，  int[4] *
//     p = &a;

//     //如何通过p访问a[3]的元素，并且打印出来！！
//    // a[3] == *(&a[3])  == *(&a[0]+3) == *(a+3) == *(*(&a)+3) == *(*(p)+3);
//     printf("%d\n",*(*(p)+3));

        // int a[3][4]={1,2,3,4,5,6,7,8,9,10,11,12};
        // int (*p)[4];   //数组指针
        // p = a;  
        // printf("%d\n",p[1][2]);  //7
        // printf("%d\n",p[0][11]);  //12

        // p = a+1;
        // printf("%d\n",p[1][2]);  //11

        // p = a   === p = &a[0]
        // p[1][2]=*(*(p+1)+2)=*(*(&a[1])+2)=*(a[1]+2) = *(&a[1][0]+2) = *(&a[1][2]) = a[1][2];
       int a[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
            printf("%p %p %p \n",a,&a-1,&a+1);
          

         int b[3][4] = {1,2,3,4,
                        5,6,7,8,
                        9,10,11,12
                        };
                    printf("%p %p %p %p\n",b,b+1,&b+1,b[1]+1);

        int c[5]= {1,2,3,4,5};
                    int *ptr;
                    ptr = (int *)(&c+1);
                    printf("%d\n",*(ptr-1));


      
}


