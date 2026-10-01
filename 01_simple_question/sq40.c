#include <stdio.h>

void reverse_arr(int arr[][3],int len)
{
    for(int i=0;i<len;++i)
    {
         for(int j=i+1;j<len;++j)
        {
            int temp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = temp;
        }
    }    
}

int main()
{
    int arr[3][3] = {0};
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<3;++j)
        {
            scanf("%d",&arr[i][j]);
        }
    }
    int sum = 0;
    for(int i=0;i<3;++i)
    {
        sum += arr[i][i];
    }
    reverse_arr(arr,3);
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<3;++j)
        {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    printf("%d",sum);
    return 0;
}