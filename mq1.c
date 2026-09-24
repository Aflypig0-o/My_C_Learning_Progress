#include <stdio.h>

int count_inversions(int arr[],int len)
{
    int count = 0;
    for(int i=0;i<len;++i)
    {
        for(int j=i+1;j<len;++j)
        {
            if(arr[i] > arr[j])
            ++count;
        }
    }
    return count;
}

int main()
{
    int arr[3] = {0};
    int n = 3;
    for(int i=0;i<n;++i)
    {
        scanf("%d",&arr[i]);
    }
    int tau = count_inversions(arr,n);
    printf("%d",tau);
    return 0;
}