#include <stdio.h>

int gcd(int a,int b)
{
    if(b == 0)
    {
        return a;
    }
    return gcd(b,a%b);
}

void sort(int *a,int *b)
{
    if(*b > *a)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}
int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    if(a == 0 || b == 0)
    {
        printf("are you a big sb ? please correct your inputs");
        return 0;
    }
    sort(&a,&b);
    int result = gcd(a,b);
    printf("%d",result);
    return 0;
}