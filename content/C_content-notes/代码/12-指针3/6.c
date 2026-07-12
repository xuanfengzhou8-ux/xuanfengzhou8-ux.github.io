#include <stdio.h>
#include <string.h>
int main()
{
    char s[2];
    strcpy(s,"12356");

    strcpy 有一个巨大的的bug
    它没有考虑越界的问题，有可能回到内存越界或非法访问！！

    char s1[8];
    char s2[8]={"abcde"};
            //运行时刻，系统会为s1分配8个字节的空间，为s2分配8个字节的空间。
            //一般来说（也不一定），编译器会把s1和s2 的 空间连续安排

    printf("%s\n",s2);    //%s 按字符串输出。

    strcpy(s1,"0123456789");

    printf("%s\n",s1);
    printf("%s\n",s2);

    一个巨大的bug

    创建一个strncpy的函数！！
    
    char *strncpy(char *dest, const char *src, size_t n);
    strncpy就是为了解决strcpy的这个bug而产生的！！
        strncpy 用来把src指向的字符串拷贝到dest指向的空间中去，但是他顶多拷贝n个字符。那么strbcpy到底拷贝了多少个字符呢？？   <= n
        (1)、遇到\0拷贝结束（\0会拷贝）
        (2)、已经拷贝n个字符啦结束（\0就不会自动拷贝啦）
     
    char a[4];
    strncpy(a,"abcdef",4);  //如果拷贝完了n个数据，但是没有找到‘\0,后面不会去补'\0'，会直接结束拷贝
    printf("%s\n",a);

    char s[2];
    strcpy(s,"ab"); //会越界
    printf("%s\n",s);

    char *p = "abcdef";
    strcpy(p,"ABC");   //报错，”abcdef“是一个只读的区域

    char a[100];
    strcpy(a,"abcdef\0cdef");
    printf("%s\n",a);
       
}