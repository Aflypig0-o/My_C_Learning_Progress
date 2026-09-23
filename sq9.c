#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n;
    bool prime_number = true;
    int remainder;
    scanf("%d",&n);
    if (n < 2)
    {
        printf("不是素数");
    }
    else
    {
        for(int i=2;i*i<=n;i++)
        {
            remainder = n%i;
            if (remainder == 0)
            {
                prime_number = false;
                break;
            }
        }
        if(prime_number == true)
        {
            printf("是素数");
        }
        else
        {
            printf("不是素数");
        }
    }
    return 0;
}