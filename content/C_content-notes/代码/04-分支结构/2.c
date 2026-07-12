
# include <stdio.h>

//判断三角形

int main()
{
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    if(a+b>c && a+c>b && b+c>a)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
    return 0;
}