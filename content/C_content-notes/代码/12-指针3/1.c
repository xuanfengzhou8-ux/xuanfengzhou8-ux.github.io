#include <stdio.h>

int main()
{
    char *p = "abc";

    printf("%c\n",*p);

    char ch = *p;
    printf("%c\n",ch);

   

    // *p = 'A'; //error,非法的内存访问

    // p+1;// 保存的‘b’的地址
    // p+2;//  ....
    // p+3;//  保存的'\0'的地址


    p = "123";   //没有问题，p是一个变量，有左值的

    printf("%c\n",*p);
}