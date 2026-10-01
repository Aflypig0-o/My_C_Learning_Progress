#include <stdio.h>
#define MAX 100

int main()
{
    int arr[MAX] = {0};
    for(int i=0;i<5;++i)
    {
        scanf("%d",&arr[i]);
    }
    for(int i=0;i<5;++i)
    {
        printf("%d ",arr[i]);
    }
    return 0;
}