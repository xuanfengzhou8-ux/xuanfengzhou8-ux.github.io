#include <stdio.h>
int main()
{
  int day,month,year,sum,leap;
  printf("\nplease input year,month,day\n");
  scanf("%d,%d,%d",&year,&month,&day);
  switch(month) /*先计算某月以前月份的总天数*/
  {
    default:printf("data error");
    case 1:sum=0;
    case 2:sum=31;
    case 3:sum=59;
    case 4:sum=90;
    case 5:sum=120;
    case 6:sum=151;
    
    
  }
 
  printf("It is the %dth day.",sum);
    
}
