/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-29 11:17:32
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-29 11:39:31
 * @FilePath: \CS22272\11指针2\code\7.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>


int sum(int a,int b)
{

}
sum是一个带着两个参数，第一个参数是int类型，第二个参数是int类型，返回值也是int类型！！

typeof(sum) : int(int ,int)

定义一个指针p，来保存函数sum的地址！！（函数指针就是一个函数的地址！！）

typeof(sum) *p;


int (int , int) *p;  ======> int (*p) (int , int);


int find_max(int *b , int n)
{

}

typeof(find_max) : int ( int * , int);
定义一个指针，来保存函数find_max的地址！
typeof(find_max) *p;
int(int * ,int ) *p   ===> int (*p)(int * ,int);




void abc(int b[] , double f)
{

}

定义一个指针p，来保存函数abc的地址！！，该如何定义！


void (*p)(int [], double);
void (*p)(int *, double);


普通的函数调用：
    函数名（实参表达式列表）
        sum(3,5)；

        p = find_max;
        p = &find_max;

        *p ====> *&find_max ====> find_max

        *函数指针 ==》 指向的函数

        通过函数指针来调用函数：
        （1）、
            （*函数指针）（实参表达式列表）;
        （2）、
            函数指针名（实参表达式列表）；
                p=find_max;
                p的右指针就是一个函数的地址！！
                p(a,5) ==== >find_max(a,5)