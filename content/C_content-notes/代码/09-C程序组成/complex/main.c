/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-05 14:12:21
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-05 14:26:41
 * @FilePath: \CS22272\09C程序组成\code\complex\main.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

#include "complex.h"

#include <stdlib.h>

int main()
{
    complex_t *p1 = complex_create(3,4);
    complex_t *p2 = complex_create(3,8);

    complex_t *p3 = complex_add(p1,p2);


    print_complex(p3);


    free(p1);
    free(p2);
    free(p3);

    return 0;
}
