#include <stdio.h>

int main()
{
    int i,j;
    int arr_a[2][3] = {0};
    int arr_b[3][2] = {0};
    for(i=0;i<2;++i)
    {
        for(j=0;j<3;++j)
        {
            scanf("%d",&arr_a[i][j]);
        }
    }

    for(j=0;j<3;++j)
    {
        for(i=0;i<2;++i)
        {
            arr_b[j][i] = arr_a[i][j];
        }
    }
    for(j=0;j<3;++j)
    {
        for(i=0;i<2;++i)
        {
                printf(" %d",arr_b[j][i]);
        }
        printf("\n");
    }
    return 0;
}