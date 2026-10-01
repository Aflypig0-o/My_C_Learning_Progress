#include <stdio.h>

void reverse_array(int *arr,int n)
{
    int *left = arr;
    int *right = arr+n-1;
    while(left < right)
    {
        int temp = *left;
        *left = *right;
        *right = temp;
        ++left;
        --right;
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    if(n<=0)
    {
        return 1;
    }
    int arr[n];
    for(int i=0;i<n;++i)
    {
        scanf("%d",&arr[i]);
    }
    reverse_array(arr,n);
    int *p =arr;
    for(int i=0;i<n;++i)
    {
        printf("%d",*p);
        ++p;
    }
    return 0;
}