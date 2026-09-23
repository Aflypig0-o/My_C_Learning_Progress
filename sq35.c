#include <stdio.h>

void min_max(int arr[],int len,int *max,int *min)
{
    *max = arr[0];
    *min = arr[0];
    for(int i=0;i<len;++i)
    {
        if(arr[i]>*max)
        {
            *max = arr[i];
        }
        if(arr[i]<*min)
        {
            *min = arr[i];
        }
    }
}

int main()
{
    int n,max,min;
    scanf("%d",&n);
    int arr[100] = {0};
    for(int i=0;i<n;++i)
    {
        scanf("%d",&arr[i]);
    }
    min_max(arr,n,&max,&min);
    printf("%d %d",max,min);
    return 0;
}