/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-21 09:32:01
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-21 09:44:09
 * @FilePath: \CS22272\06数组\code\zouye4.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
// 将整数m插入到升序数组中去，使插入后的数组a仍然有序



// 3 4 6 7 8     插入一个 5


// 我循环一次找到第一个比它大的数就可以知道它的下标位置！！






#include <stdio.h>




int main()
{
	
	int n,x,k;
	int a[n];

	printf("请输入一个数组大小，如5\n");
	scanf("%d",&n);

	printf("请输入一个递增数组\n");
    int i;
	for( i= 0; i < n ; i++)
	{
		scanf("%d",&a[i]);
	}

    printf("请输入你想插入的数值\n");
	scanf("%d",&x);



	int j;
    int b[n+1];
    for(i=0;i<n;i++)
    {
        b[i] = a[i];
    }

	if(x >= a[n-1])//如果x比所有元素都大，直接放到最后 
	{
		b[n] = x;
	}
	else
	{
		for(i = 0 ; i <= n; i++)
		{
			if(x <= b[i])
			{
				for(j = n;j > i; j--)
				{
					b[j] = b[j - 1]; 
				}		
			b[i] = x;
			break;					
			}
		}
	}


	printf("插入%d后新的数组:\n",x);
    for(k= 0; k < n+1 ; k++)
    {
        printf("%d",b[k]);
    }
    printf("\n");

}