#include <stdio.h>

int main()
{
    int sum = 0;
    int arr[5];
    for(int i=0;i < 5;i++)
    {
        scanf("%d",&arr[i]);
        sum += arr[i];
    }
    float average = sum / 5.0;
    printf("和为:%d\n平均数为:%g",sum,average);
    return 0;
}