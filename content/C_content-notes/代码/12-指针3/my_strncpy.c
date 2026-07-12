/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-08-01 14:47:52
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-01 15:24:33
 * @FilePath: \CS22272\12指针3\code\my_strncpy.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>
#include <string.h>
char *my_strcpy(char *des , char *stc)
{
    if(stc == NULL)
    {
        return NULL;
    }
    if(des == NULL)
    {
        return stc;
    }

    char *res = des;

    while(*stc)
    {
        *des = *stc;
        des++;
        stc++;
    }

    return res;
}

char * my_strncpy(char *dest , char *src , int n)
{
    int i=0;
    while(i<=n && *(src+i)!=0)
    {
        *(dest+i) = *(src+i);
        i++;
    }
    return dest;
}
int main()
{
    char str1[100]={"123456789qwertyuio"};

    char *str2 = "i am cool boy";

    //my_strcpy(str1,str2);
    strncpy(str1,str2,12);
     //my_strncpy(str1,str2,16);
    printf("%s\n",str1);

}