#include <stdio.h>

int max_array(int arr[],int n)
{
    int max = arr[1];
    for(int i=0;i<n;++i)
    {
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int main()
{
    int n;
    scanf("%d",&n);
    if(n > 0)
    {
        int arr[n];
        for(int i=0;i<n;++i)
        {
            scanf("%d",&arr[i]);
        }
        int a = max_array(arr,n);
        printf("%d",a);
        return 0;
    }
    else
    {
        return 1;
    }
}