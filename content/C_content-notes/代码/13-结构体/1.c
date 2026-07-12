/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-03 10:07:51
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-03 10:13:49
 * @FilePath: \CS22272\13结构体\code\1.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>


struct date
{
    int y;
    int m;
    int d;

};
struct student
{
    int num; // 学号
    struct date birthday;   // 生日！！
    char name[12] ;
    int score;

};
int main()
{

    struct student s;
    // scanf("%d",&s.num);
    // scanf("%s",s.name);
    // scanf("%d",&s.score);

    // scanf("%d/%d/%d",&s.birthday.y,&s.birthday.m,&s.birthday.d);
    //scanf("%d/%d/%d",&s.birthday.y,&s.birthday.m,&s.birthday.d)
    printf("%d %s %d %d/%d/%d\n",s.num,s.name,s.score,s.birthday.y,s.birthday.m,s.birthday.d);

}