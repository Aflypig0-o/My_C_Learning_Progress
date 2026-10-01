#include <stdio.h>

void double_arr(int arr[],int len)
{
    for(int i=0;i<len;++i)
    {
        arr[i] *= 2;
    }
}

int main()
{
    int arr[5] = {0};
    printf("请输入五个整数:");
    for (int i=0;i<5;++i)
    {
        scanf("%d",&arr[i]);
    }
    double_arr(arr,5);
    for(int i =0;i<5;++i)
    {
        printf("%d ",arr[i]);
    }
    return 0;
}