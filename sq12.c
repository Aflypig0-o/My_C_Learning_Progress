#include <stdio.h>
#include <stdbool.h>

    static int total_count = 0;
    static int total_sum = 0;
    static int total_factors = 0;

void analyze_number(int num,int *digit_sum, int *factor_count, bool *is_prime)
{
    *digit_sum = 0;
    *factor_count = 0;
    int temp = num;
    while(num > 0)
    {
        *digit_sum += num%10;
        num/=10;
    }

    for (int i=1;i*i <=temp;++i)
    {
        if (temp % i ==0)
        {
            ++(*factor_count);
            if (i*i != temp)
            {
                ++(*factor_count);
            }
        }
    }

    if(*factor_count == 2 && temp > 1)
    {
        *is_prime = true;
    }
    else
    {
        *is_prime = false;
    }
}

void update_totals(int num,int digit_sum,int factor_count)
{
       ++total_count;
       total_sum += num;
       total_factors += factor_count;
}

void print_summary()
{
    printf("==========全局统计报告==========");
    printf("共输入了%d个有效数字\n",total_count);
    printf("所有输入数字的总和为:%d\n",total_sum);
    printf("所有数字的因数个数总和为:%d\n",total_factors);
}

int main()
{
    int num;
    int digit_sum,factor_count;
    bool is_prime;

    while(1)
    {
        printf("请输入一个正整数:\n");
        scanf("%d",&num);
        if (num <= 0)
        {
            break;
        }
        printf("数字%d的分析结果:\n",num);
        analyze_number(num,&digit_sum,&factor_count,&is_prime);
        printf("各位数字之和:%d\n因数个数:%d\n",digit_sum,factor_count);
        if (is_prime == true)
        {
            printf("是素数\n");
        }
        else
        {
            printf("不是素数\n");
        }
        update_totals(num,digit_sum,factor_count);
    }
    print_summary();
    return 0;
}