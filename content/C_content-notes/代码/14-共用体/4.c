/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-03 16:07:08
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-03 16:31:10
 * @FilePath: \CS22272\14共用体\code\4.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
eg:
    char ---> s8
    typedef char s8;  //编译器 把类型名 s8 等同于char

    s8 a; ===> char a;

    struct student
    {
        int num;
        .....
    };
    typedef struct student STU;
    struct student s;
    STU s1;  ==== > struct student s1


    typedef struct student
    {
        int  num;
        ......
    }STU;    //编译器会把类型名 STU 等同于 struct student

    typedef struct node
    {
        int data;
        int *next;
    }Node,*NODE;

    typedef struct node Node;   //编译器吧类型名 Node 等同于 struct node
    typedef struct node *NODE;  //编译器吧类型名 NODE 等同于 struct node*

    Node s; s是一个结构体变量 struct node s
    NODE p; p是一个结构体指针变量 struct node* p


    typedef struct test
    {
        int a;
        int b;
    }T1;

    struct test
    {
        int a;
        int b;
    }T2;

    T1 是一个类型名，等同于 struct test

    T2 是一个结构体变量
    struct test T2;


    int NUM[100];

    typedef int NUM[100];   //NUM是一个新的类型名， int[100]

    typedef int[100] NUM;  -===> typedef int NUM[100];
    
    NUM a;


    int b;    //b是一个变量名
    typedef int b;  //b是一个类型名

    void (*p)(int ,float);
    p是什么？？   A
    A p是一个指针变量名
    B p是一个函数名
    C 以上都不是
    D 我不知道

    typedef void(*p)(int,float) ;    //p是一个类型名
        p 是 一个函数指针类型，指向的类型不带返回值，带两个参数，一个int ， 一个float

    
    p p1; //p1是一个函数指针名
        ===》void （*p）（int ， float）；


    void xxx（int a ， float b）
    {

    }
    p1 = xxx;
    p = xxx; // error
        