#include <stdio.h>
#include <stdbool.h>

void bubble_sort(int arr[],int len)
{
    for(int i=0;i<len-1;++i)
    {
        bool swapped = false;
        for(int j=0;j<len-1-i;++j)
        {
            if(arr[j]>arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = true;
            }
        }
        if(!swapped)
        {
            break;
        }
    }
}

int main()
{
    int n;
    scanf("%d",&n);
        if(n <= 0)
    {
        return 1;
    }
    int arr[6] = {0};
    for(int i=0;i<n;++i)
    {
        scanf("%d",&arr[i]);
    }
    bubble_sort(arr,n);
    for(int i=0;i<n;++i)
    {
        printf("%d ",arr[i]);
    }
    return 0;
}