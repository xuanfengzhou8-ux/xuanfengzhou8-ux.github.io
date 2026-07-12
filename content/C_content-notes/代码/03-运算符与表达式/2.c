#include <stdio.h>
int main()
{
    int a = ~(-3);
    printf("%d\n",a);
    printf("%u\n",a);

    int b = !(-3);
    printf("%d\n",b);
    printf("%u\n",b);

  

    return 1;
}