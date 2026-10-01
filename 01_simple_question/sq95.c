#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 3;
    int *arr =(int*)malloc(n*sizeof(int));
    if(arr == NULL)
    {
        return 1;
    }

    for(int i=0;i<n;++i)
    {
        scanf("%d",&arr[i]);
    }

    int *temp = realloc(arr,2*n*sizeof(int));
    if(temp == NULL)
    {
        free(arr);
        return 2;
    }
    arr = temp;

    for(int i=n;i<2*n;++i)
    {
        scanf("%d",&arr[i]);
    }

    for(int i=0;i<2*n;++i)
    {
        printf("%d ",arr[i]);
    }
    free(arr);
    arr = NULL;
    return 0;
}