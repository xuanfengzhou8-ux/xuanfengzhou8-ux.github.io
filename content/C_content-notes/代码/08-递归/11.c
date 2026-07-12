/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-26 09:34:13
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-26 11:05:26
 * @FilePath: \CS22272\08递归\code\11.c
 * @Description: 


 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include <stdio.h>

void int_char_ascii(unsigned int value)
{
    unsigned int num;
    num = value / 10;
    
    if(num !=0 )
    {
        int_char_ascii(num);
    }  
    printf("%c ",value % 10 + '0');  
  
}


int main()
{
    int_char_ascii(4267);
    return 1;
}



