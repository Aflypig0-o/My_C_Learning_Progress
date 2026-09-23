#include <stdio.h>
#define PRINT_SUM(arr,len) do \
{\
    int _sum = 0;\
    for(int _i=0;_i<(len);++_i)\
    {\
        _sum += (arr)[_i];\
    }\
    printf("%d",_sum);\
}while(0)

int main()
{
    int arr[5] = {0};
    for(int i=0;i<5;++i)
    {
        scanf("%d",&arr[i]);
    }
    PRINT_SUM(arr,5);
    return 0;
}