// Sn = a + aa + .... +a...a(n个a),n,a由用户输入，a属于[0,9]的一个整数，n也为整数。编写一个程序求Sn.

#include <stdio.h>


int main()
{
    int i,a,n;

    long s = 0 ,t = 0;
    scanf("%d%d",&a,&n);

    for(i = 1 ; i <= n ; i++)
    {
        t = t + a ;     // t = a        t = a+a0 = aa
        s = s + t ;     // s = t        s = aa
        a = a * 10;     // a = a0       a = aa0
        
    }

    printf("%ld\n",s);

    return 0;
}