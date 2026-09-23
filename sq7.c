#include <stdio.h>

int main()
{
    int sum = 0;
    int i;
    int n = 1;
    scanf("%d",&i);
    while(n <= i)
    {
        sum += n;
        n++;
    }
    printf("%d",sum);
    return 0;
}