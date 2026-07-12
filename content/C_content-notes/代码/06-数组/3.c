//判断一个一维数组是否为递增？/


#include <stdio.h>

int main()
{
    int a[5]={1,2,3,4,5};

    int flag = 1 ;  //假定当flag==1的时候，则说明数组递增，反之则，递减

    for(int i = 0 ; i < 4 ; i++)
    {
        if(a[i] > a[i+1])
        {
            flag = 0;
            break;
        }
    }
    if(flag == 1)
    {
        printf("yes\n");

    }
    if(flag == 0)
    {
        printf("no\n");
    }

    return 0;

}