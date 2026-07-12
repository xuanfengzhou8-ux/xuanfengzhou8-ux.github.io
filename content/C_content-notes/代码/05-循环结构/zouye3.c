/*
    连续的正整数之和。一个正整数有可能可以被表示为n(n>=2)个连续正整数之和：如
		15=1+2+3+4+5
		15=4+5+6
		15=7+8
*/

#include <stdio.h>

int main()
{
    int n;
    int i ,j , k ,m;
    int flag = 0;

    scanf("%d",&n);

    for(i = 1 ; i < (n+1)/2 ; i++)    //记录你成功匹配之后的，那个起始位置
    {
        k = 0;
        for(j=i;j<n;j++)
        {
            k+=j;
            if(k>=n)
            {
                break;
            }
        }
        if(k==n)
        {
            printf("%d=%d",n,i);
            for(m=i+1;m<=j;m++)
            {
                printf("+%d",m);
            }
            printf("\n");
            flag=1;
        }
    }
    if(flag == 0)
    {
        printf(" 你是个小趴菜！！！\n");
    }
}