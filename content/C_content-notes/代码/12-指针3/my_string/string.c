/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-02 09:00:22
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-02 09:34:04
 * @FilePath: \CS22272\12指针3\code\my_string\string.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */





strlen:
    int m_strlen(char *s)
    {
        int n =0;
        while(*s++)    //while(*s) { s++ , n++}
        {
            n++;
        }
        return n;
    }

strcmp:
    int m_strcmp(char *p , char *s)
    {
        while(*p||*s)
        {
            if(*p > *s)
            {
                return 1;
            }
            else if(*p<*s)
            {
                return -1;
            }
            p++;
            s++;
        }

        return 0;
    }


strncmp:
    int m_strncmp(char *p , char *s , int n)
    {
        while(n-- && (*p||*s))
        {
            if(*p > *s)
            {
                return 1;
            }
            else if(*p<*s)
            {
                return -1;
            }
            p++;
            s++;
        }
        return 0;
    }


strcpy:
    char * m_strcpy(char *dest , char *src)
    {
        char *p = dest;
        while((*dest++ = *src++));
        return p;
    }


strncpy:
    char * strncpy(char  *dest , char *src , int n)
    {
        char *p = dest;
        while(n--&&(*dest++ = *src++));
        return p;
    }

strcat:
    char *strcat(char * dest , char *src)
    {
        char * p = dest;
        while(*dest) 
        {
            dest++;
        }
        while(*dest++ = *src++);
        return p;
    }

strncat:
    char *strncat(char *dest , char *src , int n)
    {
        char * p = dest;
        while(*dest)
        {
            dest++;
        }
        while(n--&&*dest++ = *src++);

        return p;
    }



    puts();    函数用来向标准输出设备屏幕 输出字符串 并且 换行！！！
    getchar();    函数只能用于单个字符的输入，一个输入一个字符
    gets();       用于对字符串的输入！！


    char *p,*q;
    p = (char *)malloc(sizeof(char) * 20);
    q = p;
    scanf("%s%s",p,q);      //abcd f(回车)   覆盖
    printf("%s%s\n",p,q);