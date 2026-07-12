/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-05 11:17:20
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-05 14:11:43
 * @FilePath: \CS22272\09C程序组成\code\complex\complex.h
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#ifndef __COMPLEX_X__
#define __COMPLEX_X__



typedef struct complex
{
    double real;   //实部
    double imag;    //虚部
}complex_t;


/**
 * @description:   创建一个复数
 * @param {double} r  ： 复数的实部
 * @param {double} i  ： 复数虚部
 * @return {*}返回值是返回一复数结构体的地址
 */
complex_t * complex_create(double r, double i);



/**
 * @description:   复数求和
 * @param {complex_t} *p1   ： 第一个复数的地址
 * @param {complex_t} *p2   ： 第二个复数的地址
 * @return {*}  返回值：返回一个新的复数的地址
 */
complex_t * complex_add(complex_t *p1,complex_t *p2);


/**
 * @description:   打印一个复数
 * @param {complex_t} *a
 * @return {*}
 */
void print_complex(complex_t *a);




#endif