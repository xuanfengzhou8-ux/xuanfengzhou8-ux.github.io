#include <stdio.h>


void func(int * p)
{
    //p指向main函数中的a
    // p = &main.a
    //*p = *&main.a=main.a

    *p = 250;
}


int main()
{
    int a;
    func(&a);
    printf("%d\n",a);
}