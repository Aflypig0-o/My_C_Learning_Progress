#include <stdio.h>

int main()
{
    int positive_number =0;
    int negative_number = 0;
    int zero = 0;
    int arr[10] = {0};
    for(int i=0;i<10;++i)
    {
        scanf("%d",&arr[i]);
        if (arr[i] > 0)
        {
            ++positive_number;
        }
        else if (arr[i] == 0)
        {
            ++zero;
        }
        else
        {
            ++negative_number;
        }
    }
    printf("正数一共有%d个\n负数一共有%d个\n零有%d个",positive_number,negative_number,zero);
    return 0;
}