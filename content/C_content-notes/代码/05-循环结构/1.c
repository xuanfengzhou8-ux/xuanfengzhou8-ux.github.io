#include <stdio.h>
/*
    逆序输出一个正整数的各个位上数字
*/

int main()
{
    int a;
    int d;
    scanf("%d",&a);
    while(a)
    {
        d = a % 10;
        printf("%d",d);
        a = a/10;
    }
    printf("\n");
    return 0;
}