#include <stdio.h>

int main()
{
    int a =5 , b =6;
    a = (a = 6 , a + b );
    printf("%d\n",a);


    printf("%ld\n",sizeof(typeof(1.0)));
    return 1;
}