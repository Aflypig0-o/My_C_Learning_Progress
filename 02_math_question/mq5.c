#include <stdio.h>
#define MAX 3

double minor(double d[3][3],int r,int c,int len)
{
    double result;
    double det_m[2][2] = {0};
    int x = 0;
    int y = 0;
    for(int i=0;i<len;++i)
    {
        if(i == (r-1))
        {
           continue;
        }
        for(int j=0;j<len;++j)
        {
            if(j == (c-1))
            {
                continue;
            }
            det_m[x][y] = d[i][j];
            ++y;
        }
        y-=(len-1);
        ++x;
    }
    for(int i=0;i<(len-1);++i)
    {
        for(int j=0;j<(len-1);++j)
        {
            printf("%g ",det_m[i][j]);
        }
        printf("\n");
    }
    result = det_m[0][0] * det_m[1][1] - det_m[0][1] * det_m[1][0];
    return result;
}

int main()
{
    double minor_result,cofactor_result;
    double det_minor = 0;
    double det[3][3] = {0};
    int n = MAX;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            scanf("%lf",&det[i][j]);
        }
    }
    int row,col;
    scanf("%d%d",&row,&col);
    minor_result = minor(det,row,col,n);
    int sign = (row+col)%2;
    if(!sign)
    {
        cofactor_result = minor_result;
    }
    else
    {
        cofactor_result = -1*minor_result;
    }
    printf("%g\n",minor_result);
    printf("%g\n",cofactor_result);
    return 0;
}