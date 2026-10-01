#include <stdio.h>

int main()
{
    int sum = 0;
    int arr[3][3] = {0};
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<3;++j)
        {
            scanf("%d",&arr[i][j]);
        }
    }

    for(int i=0;i<3;++i)
    {
        sum += arr[i][i];
    }

    printf("%d",sum);
    return 0;
}