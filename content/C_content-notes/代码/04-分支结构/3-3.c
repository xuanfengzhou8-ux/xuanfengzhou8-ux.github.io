#include <stdio.h>
#include <math.h>

int main()
{
    double x,y;
    scanf("%lf",&x);
    if(x>6)
    {
        y = 5.0/27*(pow(x,2)+4*x-6);
    }
    else if(x<=0)
    {
        y = 23.0/7 * fabs(pow(x,3)+4);
    }
    else
    {
        y = log(16)/log(3)+x;
    }
    
    printf("%.3f\n",y);
    return 0;
}
//表达数学表达式中 2/5 = 0.4
//C语言中需要怎么写！！  2 *1.0 / 5 = 0.5  