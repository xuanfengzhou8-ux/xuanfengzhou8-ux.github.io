/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-22 09:04:44
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-22 09:32:12
 * @FilePath: \CS22272\06数组\code\2zouye4.c
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
//高数巨占位


// #include <stdio.h>


// int main()
// {
//     int a[3][4]={0};
//     int i,j;
//     for(i=0;i<3;i++)
//     {
//         for(j=0 ; j<4 ;j++)
//         {
//             scanf("%d",&a[i][j]);
//         }
//     }
//     printf("please input need : \n");
//     int k;
//     scanf("%d",&k);

//     int b=0;   //用来保存有多少种坐的方式！！

//     int c = 0;   //这个c是我用来计数！！
//     int sum = 0;  //求和！！
//     for(i = 0 ; i < 3 ; i++)
//     {
//         c = 0 ;
//         for(j=0 ; j<4 ; j++)
//         {
//             sum = sum + a[i][j];
//             if(sum == 0)
//             {
//                 c++;   //一个为0.则记一个位置！！
//             }
//             else if(sum == 1)   //出现1 ，重新记数
//             {
//                 sum = 0;    //对sum重新赋值
//                 c = 0;      //此时，我们的计数器也需要重新赋值
//             }
//             if(c>=k)
//             {
//                 b++;
//             }
//         }
//     }

//     if(b == 0)
//     {
//         printf("高数巨逃课，寄了\n");
//     }
//     else
//     {
//         printf("有%d种和室友甜甜蜜蜜的方式\n",b);   
//     }

// }


//这个老六我真的服了 09:20:04

#include <stdio.h>

//“高数巨”占座位的问题
int main() {
	int k, i, j;
	int g = 0;
	int w = 0;
	printf("请输入K值\n");
	scanf("%d", &k);
	printf("请输入行数和列数\n");
	scanf("%d%d", &i, &j);
	int a[i][j];//定义一个这么大小的数组
	printf("请输入一个%d行%d列数组\n", i, j);
	for (int m = 0; m < i; m++) {
		for (int n = 0; n < j; n++) {
			scanf("%d", &a[m][n]); //写入数组
		}
	}


	for (int c = 0; c < i; c++) 
    { //遍历数组的行
		for (int d = 0; d < j; d++) 
        { //遍历数组的列
			for (int y = 0; y < k; y++)
             {
				if (d + y < j) 
                {
					if (a[c][d + y] == 0)
                    {
						w += 1;

					}
				}
			}
			if (w == k)
            {
				g++;
			}
			w = 0;
		}
	}


	printf("高数巨能占座的情况有%d种", g);
	return 0;
}
