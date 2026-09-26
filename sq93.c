#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sum = 0;
    int n;
    scanf("%d",&n);
    int *arr = (int*)malloc(n * sizeof(int));
    if(arr == NULL)
    {
        return 1;
    }
    for(int i=0;i<n;++i)
    {
        scanf("%d",&arr[i]);
    }
    for(int i=0;i<n;++i)
    {
        sum += arr[i];
    }
    printf("%d",sum);
    free(arr);
    arr = NULL;
}