#include <stdio.h>

int main()
{
    int grade;
    scanf("%d",&grade);
    if(grade >= 90 && grade <=100)
    {
        printf("A\n");
    }
    if(grade >=80 && grade <=90)
    {
        printf("B\n");
    }


    return 0;
}

