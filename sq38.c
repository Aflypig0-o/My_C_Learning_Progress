#include <stdio.h>

int main()
{
    int arr[3][4] = {0};
    int sum_x[3] = {0};
    int sum_y[4] = {0};
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<4;++j)
        {
            scanf("%d",&arr[i][j]);
        }
    }
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<4;++j)
        {
            sum_x[i] += arr[i][j];
        }
        printf("第%d行合为:%d\n",i+1,sum_x[i]);
    }
    for(int j=0;j<4;++j)
    {
       for(int i=0;i<3;++i)
       {
        sum_y[j] += arr[i][j];
       }
       printf("第%d列合为:%d\n",j+1,sum_y[j]);
    }
    return 0;
}