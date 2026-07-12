#include <stdio.h>


int main()
{
    int hour,min;
    scanf("%d:%d",&hour,&min);
    if(hour > 12)
    {
        hour -= 12;
        printf("%d:%d PM",hour,min);
    }
    else if(hour == 12)
    {
        printf("%d:%d PM",hour,min);
    }
    else
    {
         printf("%d:%d AM",hour,min);
    }
    return 0;
}