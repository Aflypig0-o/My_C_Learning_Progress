#include <stdio.h>
#define MAX 100

int  calc_sum(int arr[],int n)
{
    int sum = 0;
    if(n == 0)
    {
        return 0;
    }
    sum += arr[n-1] + calc_sum(arr,n-1);
    return sum;
}

int main()
{
    int result;
    int arr[MAX] = {0};
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&arr[i]);
    }
    result = calc_sum(arr,n);
    printf("%d",result);
    return 0;
}