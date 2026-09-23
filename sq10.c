#include <stdio.h>

void analyze(int *x,int *y,int *count,int *sum)
{
    *count = 0;
    *sum = 0;
    int temp1 = *x;
    int temp2 = *y;
    int remainder;
    while (temp1 <= temp2)
    {
        if(temp1 >= 2)
        {
            for(unsigned int i = 2;i*i<=temp1;++i)
            {
                remainder = temp1 % i;
                if(remainder == 0)
                {
                    ++(*count);
                    *sum += temp1;
                    break;
                }
            }
        }
        ++temp1;
    }

}
int main()
{
    int m,n,count,sum;
    scanf("%d%d",&m,&n);
    if (m < n)
    {
        analyze(&m,&n,&count,&sum);
        printf("%d\n%d",count,sum);
    }
    else
    {
        printf("意外的输入,请确保m小于n");
    }
    return 0;
}