# include <stdio.h>



int main()
{
    int x ; 
    int a,b,c;
    for(x = 100 ; x < 1000 ; x++)
    {
        a = x % 10;
        b = x/10%10;
        c = x /100;
        if(a * a * a + b * b * b + c * c * c  == x)
        {
            printf("%d\n",x);
        }  
    }
    return 0;
}