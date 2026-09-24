#include <stdio.h>

int factorial(int n)
{
    if(n<=1)
    {
        return 1;
    }
    return n*factorial(n-1);
}
int main()
{
    int number;
    scanf("%d",&number);
    if(number<0)
    {
        printf("unexpected input,please ensure the number is greater than 0\n");
        return 0;
    }
    int c = factorial(number);
    printf("%d",c);
    return 0;
}