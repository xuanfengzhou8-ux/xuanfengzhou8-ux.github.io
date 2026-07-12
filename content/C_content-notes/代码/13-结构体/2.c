/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-03 14:01:20
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-03 14:13:48
 * @FilePath: \CS22272\13结构体\code\2.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

struct student
{
    char name[10];
    int score;
}students[5];


void swap(struct student stu[], int a , int b)
{
    struct student s = stu[a];    //int temp;
    stu[a] = stu[b];
    stu[b] = s;
}

void Structsort(struct student stu[], int n)
{
    for(int i = 0; i<n ; i++)
    {
        int m = i ;
        for(int j = i ; j<n ; ++j)
        {
            if(stu[m].score < stu[j].score)
            {
                m = j;
            }
        }
        if(m!=i)
        {
            swap(stu,m,i);
        }
    }
}


int main()
{
    for(int i = 0; i<=4 ; i++)
    {
        scanf("%s%d",students[i].name,&students[i].score);
    }
    Structsort(students,5);
    for(int i = 0; i<=4 ; i++)
    {
        printf("%s %d\n",students[i].name,students[i].score);
    }
    return 0;
}

