/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-05 11:19:06
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-05 14:17:40
 * @FilePath: \CS22272\09C程序组成\code\complex\complex.c
 * @Description:
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */ 

#include "complex.h"
#include <stdlib.h>
#include <stdio.h>


complex_t * complex_create(double r, double i)
{
    // complex_t t;
    // t.real=r;
    // t.imag =i  
    // return t;

    //函数返回一个非static的局部变量的地址是有问题

    complex_t *t = malloc(sizeof(complex_t));
    t->real = r;
    t->imag = i;
    return t;
}

complex_t * complex_add(complex_t *p1,complex_t *p2)
{
    complex_t * t = malloc(sizeof(*t));
    t->real = p1->real+p2->real;
    t->imag = p1->imag +p2->imag;

    return t; 
}


void print_complex(complex_t *a)
{
    printf("%f ",a->real);
    if(a->imag >=0)
    {
        printf("%+fi\n",a->imag);
    }
    else
    {
        printf("%fi\n",a->imag);
    }
}
