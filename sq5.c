#include <stdio.h>

void divide(int a,int b,int *quotient,int *remainder)
{
    *quotient = a/b;
    *remainder = a%b;
}
int main()
{
    int x,y,quotient,remainder;
    scanf("%d%d",&x,&y);
    divide(x,y,&quotient,&remainder);
    printf("%d\n%d",quotient,remainder);
    return 0;
}