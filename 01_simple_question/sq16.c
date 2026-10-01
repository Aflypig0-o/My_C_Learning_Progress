#include <stdio.h>

void reverse_arr(int arr[],int len)
{
    int left = 0;
    int right = len-1;
    int temp;
    while(left < right)
    {
        temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        ++left;
        --right;
    }
}

int main()
{
    int arr[5] = {0};
    for(int i=0;i<5;++i)
    {
        scanf("%d",&arr[i]); 
    }
    reverse_arr(arr,5);
    for(int i=0;i<5;i++)
        {
            printf("%d\n",arr[i]);
        }
    return 0;
}