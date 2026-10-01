#include <stdio.h>

int main()
{
    int arr[3][4] = {0};
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
            if(j==0)
            {
                printf("%d ",arr[i][j]);
            }
            else
            {
                printf(" %d ",arr[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}