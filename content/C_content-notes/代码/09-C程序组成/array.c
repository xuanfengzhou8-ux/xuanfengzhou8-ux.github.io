#include <stdio.h>


int Quicksort(int a[],int low,int high);
int Sort(int a[],int low,int high);

void array_input(int a[],int n)
{
    puts("请输入数组的元素值：");
    for(int i=0;i<n;i++)
    {
        scanf("%d",a+i);
    }
}
int array_sum(int a[],int n)
{
    int sum=0;
    for(int i=0;i<n;i++)
    {
        sum+=a[i];
    }
    return sum;
}
int array_max(int a[],int n)
{
    int max=a[0];
    for (int i = 1; i < n; i++)
    {
        if(max<a[i])
        {
            max=a[i];
        }
    }
}
void array_sort(int a[],int n)
{
    Quicksort(a,0,n-1);
}
int Quicksort(int a[],int low,int high)
{
    int mid;
    if(low<high)
    {
        mid=Sort(a,low,high);
        Quicksort(a,mid+1,high);
        Quicksort(a,low,mid-1);
    }
}
int Sort(int a[],int low,int high)
{
    if(low<high)
    {
        int flag=a[low];
        while (low<high&&flag<a[high])
        {
            high--;
        }
        int temp=a[low];
        a[low]=a[high];
        a[high]=temp;
        while (low<high&&flag>a[low])
        {
            low++;
        }
        temp=a[low];
        a[low]=a[high];
        a[high]=temp;
    }
    return low;
}
void array_print(int a[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    putchar('\n');
}









