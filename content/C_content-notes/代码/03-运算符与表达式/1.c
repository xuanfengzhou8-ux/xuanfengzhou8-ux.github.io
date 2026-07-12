#include <stdio.h>
int main()
{
    int a,b,c,d,m,n;
    a=1 ; 
    b=2 ; 
    c=3 ;
    d=4 ;
    m=1;
    n=1;
    (m=a>b)&&(n=c>d);
    printf("%d %d %d %d %d %d\n",a,b,c,d,m,n);  //1 2 3 4 0 1 
}