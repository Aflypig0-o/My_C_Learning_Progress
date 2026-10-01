#include <stdio.h>

void calc(int a,int b,int *sum,int *diff,int *product)
{
    *sum = a+b;
    *diff = a-b;
    *product = a*b;
}

int main()
{
    int x,y,sum,diff,product;
    scanf("%d%d",&x,&y);
    calc(x,y,&sum,&diff,&product);
    printf("%d\n%d\n%d\n",sum,diff,product);
    return 0;
}