/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-25 14:29:39
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-25 14:29:48
 * @FilePath: \CS22272\07函数\code\1.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>


//float array_pjunz(int a, int b,int c);

float array_pjunz(int , int ,int );

int main()

{

    float m = array_pjunz(10,20,30);
    printf("%f\n",m);
}



/**
 * @description:  求平均值
 * @param {int} a  ： 第一個參數
 * @param {int} b
 * @param {int} c
 * @return {*}：返回值三個書的平均值
 */
float array_pjunz(int a , int b ,int c)

{

    int sum = a+b+c;

    float n = sum * 1.0 / 3;

    return n;

}