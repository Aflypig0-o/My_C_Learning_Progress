#include <stdio.h>
#include <stdbool.h>

void bubble_sort(int *arr,int len)
{
    for(int i=0;i<len-1;++i)
    {
        bool swapped = false;
        for(int *p = arr;p<arr+len-1-i;++p)
        {
            if(*p > *(p+1))
            {
                int temp = *p;
                *p = *(p+1);
                *(p+1) = temp;
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
    int arr[6] = {0};
    for(int i=0;i<6;++i)
    {
        scanf("%d",&arr[i]);
    }
    bubble_sort(arr,6);
    for(int i=0;i<6;++i)
    {
        printf("%d ",arr[i]);
    }
    return 0;    
}