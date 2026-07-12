/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-29 09:41:44
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-29 10:12:52
 * @FilePath: \CS22272\11指针2\code\3.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>


/**
 * @description:   交换
 * @param {int} *a ： 第一个整数的地址
 * @param {int} *b ： 第二个整数的地址
 * @return {*} ：无
 */
void swap(int *x ,int *y)
{   
    //x = 第一个整数的地址
    //*x => 第一个整数
    // typeof(x) : int *
    // typeof (*x) : int
    int t;
    t = *x;
    *x = *y;
    *y = t;
}

void swap_e1(int *a ,int *b)
{
    // *a = *a ^ *b;            //^ 位运算， 要求两个操作数，都必须为整数
    // *b = *b ^ *a;
    // *a = *a ^ *b;
}


void swap_e3(int *x ,int *y)
{   
    //只是交换了swap_e3函数内，变量x，y的值
    //x指向的对象和y指向的对象，根本没动
    printf("x=%d y=%d\n",*x,*y);
    int *temp;
    temp = x;
    x = y;
    y = temp;
    printf("x=%d y=%d\n",*x,*y);
}

int main()
{
    int a = 250;
    int b = 520;
    //swap(&a,&b);
    swap_e1(&a,&b);
    printf("a=%d,b=%d\n",a,b);
    
}