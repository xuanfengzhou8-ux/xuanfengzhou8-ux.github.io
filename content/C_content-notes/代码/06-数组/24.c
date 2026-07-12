// 矩阵乘法


#include <stdio.h>

#define N 3
#define M 3
#define K 2

int main()
{
    int a[M][K];    //矩阵A
    int b[K][N];    //矩阵B
    int c[M][N]={0};   //矩阵c  最终的结果矩阵

    int i ,j ;
    printf("please input A :\n");
    for(i=0;i<M;i++)
    {
        for(j=0 ; j<K ;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    printf("please input B:\n");
    for(i=0;i<K;i++)
    {
        for(j=0 ; j<N ;j++)
        {
            scanf("%d",&b[i][j]);
        }
    }
    int t ;
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            for(t=0;t<K;t++)
            {
                c[i][j] = c[i][j] + a[i][t] * b[t][j];
            }
        }
    }

    for(i=0;i<M;i++)
    {
        for(j=0 ; j<N ;j++)
        {
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }
    return 0;
    

}