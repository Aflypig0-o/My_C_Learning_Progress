#include <stdio.h>
#define MAX 100

int find_max(int arr[],int n)
{
    if(n == 1)
    {
        return arr[0];
    }
    int prev_max = find_max(arr,n-1);
    if(arr[n-1] > prev_max)
    {
        return arr[n-1];
    }
    else
    {
        return prev_max;
    }
}

int main()
{
    int arr[MAX],n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&arr[i]);
    }
    int max = find_max(arr,n);
    printf("%d",max);
    return 0;
}