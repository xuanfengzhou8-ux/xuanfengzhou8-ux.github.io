#include <stdio.h>

man atoi

1、设计一个函数，把一个是镜子的数字字符串，转换成一个整数。
    “365”----》365

    （1）、明确任务目标
        atoi：把一个十进制的数字字符串，转换成整数
    （2）、确定任务的输入参数
        “字符串”
        atoi（char *s）
    （3）、确定完成任务的返回值
        int atoi（char *s）

    （4）具体的是实现代码
    
    int atoi(cahr *s)
    {
        int flag;
        int num =0;
        if(*s == '-')
        {
            flag = 0;
            s++;
        }
        else
        {
            flag = 1;
            if(*s == '+')
            {
                s++;
            }
        }

        //s指向数字字符！！
        while(*s)
        {
            //先获取当前位的“位值”
            int d = *s - '0';

            //累加到num，让num按十进制左一位（把最低位空出出来）+d
            num = num * 10 + d;
            s++;
        }

        if(flag == 0)
        {
            num = num*(-1);
        }
        return num;
    }