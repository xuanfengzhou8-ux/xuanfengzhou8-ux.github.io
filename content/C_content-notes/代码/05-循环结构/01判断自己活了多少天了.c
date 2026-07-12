

#include <stdio.h>


//判断年份y是不是闰年！！
//返回值：如果返回1 表示是闰年
//如果返回 0 ，表示不是闰年
//参数：int y 传入年份
int is_ruinian(int y)
{
    if((y % 4 == 0 && y%100 != 0) || (y%400 == 0))
    {
        return 1;
    }
    return 0;
}
/*
    //(1)算一下出生日期距离当年年末的天数
	//(2)出生的第二年到去年的天数
	//(3)当前日期距离年初的天数！！
*/

//算一个日期(年月日)距离年初有多少天！




/**
 * @description: 
 * @param {int} y
 * @param {int} m
 * @param {int} d
 * @return {*}
 */
int get_days_from_firstday(int y ,int m , int d)
{
    int days = 0;
    //(1)[1 , m-1]
    switch(m-1)
    {
        case 11:
            days += 30;
        case 10:
            days += 31;
        case 9:
            days += 30;
        case 8:
            days += 31;
        case 7:
            days +=31;
        case 6:
            days +=30;
        case 5:
            days +=31;
        case 4:
            days +=30;
        case 3:
            days +=31;
        case 2:
            days += 28;
            if(is_ruinian(y))
            {
                days++;
            }
        case 1:
            days += 31;
    }
    days += d;
    return days;
} 

//算一个日期到年末还有多少天？？
/**
 * @description: 
 * @param {int} y
 * @param {int} m
 * @param {int} d
 * @return {*}
 */
int get_days_from_lastday(int y ,int m , int d)
{
    int days = 0;
    //[m,12]的天数
    switch(m)
    {
        case 1:
            days += 31;
        case 2:
            days += 28;
            if(is_ruinian(y))
            {
                days++;
            }
        case 3:
            days +=31;
        case 4:
            days +=30;
        case 5:
            days +=31;
        case 6:
            days +=30;
       case 7:
            days +=31;
        case 8:
            days += 31;
        case 9:
            days += 30;
        case 10:
            days += 31;
        case 11:
            days += 30;
        case 12:
            days +=31;
    }
    days -= d;
    return days;
}



/**
 * @description: 
 * @return {*}
 */
int main()
{
    int birth_y,birth_m,birth_d;		//这是你的生日   
    int cur_y , cur_m , cur_d; 			//当前日期
    int days = 0;
    printf("请你输入你的生日:\n");
    scanf("%d.%d.%d",&birth_y,&birth_m,&birth_d);
    printf("请输入当前日期:\n");
    scanf("%d.%d.%d",&cur_y,&cur_m,&cur_d);
    if((birth_y > cur_y)||(birth_y == cur_y && birth_m > cur_m)||(birth_y == cur_y&&birth_m == cur_m && birth_d > cur_d))
    {
        printf("write error\n");
        return 0;
    }
    if(birth_y != cur_y)
    {
        //(1)算一下出生日期距离当年年末的天数
        days += get_days_from_lastday(birth_y,birth_m,birth_d) ;
        //(2)出生的第二年到去年的天数
        int i;
        for(i=birth_y + 1 ; i < cur_y ; i++)
        {
            days +=365;
            if(is_ruinian(i))
            {
                days++;
            }
        }
        //(3)当前日期距离年初的天数！！
        days +=get_days_from_firstday(cur_y , cur_m , cur_d);
    }
    else	//你是今年生的
    {
       int y ,x;
        // y:当前日期距离年初的天数
       y=get_days_from_firstday(cur_y , cur_m , cur_d);
        // x:出生日期距离年初的天数
       x=get_days_from_firstday(birth_y,birth_m,birth_d);
       days = y-x;
    }
    printf("你已经活了：%d天了\n",days);
}