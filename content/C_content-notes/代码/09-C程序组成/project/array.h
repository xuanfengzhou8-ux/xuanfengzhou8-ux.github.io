/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-05 09:53:58
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-05 10:10:25
 * @FilePath: \CS22272\09C程序组成\code\project\array.h
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */

#ifndef __ARRAY_H__
#define __ARRAY_H__

struct test
{
    int a;
    int b;
};
void array_input(int a[],int n);

int array_sum(int a[],int n);

int array_max(int a[],int n);

void array_sort(int a[],int n);

int Quicksort(int a[],int low,int high);

int Sort(int a[],int low,int high);

void array_print(int a[],int n);

#endif

