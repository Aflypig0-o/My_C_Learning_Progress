#include <stdio.h>

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
    int max = arr[0][0];
    int arr_x = 1;
    int arr_y = 1;
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<3;++j)
        {
            if(arr[i][j]>max)
            {
                max = arr[i][j];
                arr_x = i+1;
                arr_y = j+1;
            }
        }
    }
    printf("%d\n",max);
    printf("[%d,%d]",arr_x,arr_y);
    return 0;
}