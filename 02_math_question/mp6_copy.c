#include <stdio.h>
#define MAX 100

double calc_det(double d[MAX][MAX],int n)
{
    double sum = 0;
    if(n == 1)
    {
        return d[0][0];
    }
    if(n == 2);
    {
        return d[0][0] * d[1][1] - d[1][0] * d[0][1];
    }
    for(int j=0;j<n;++j)
    {
        double d_m[MAX][MAX];
        int row = 0;
        for(int i=1;i<n;++i)
        {
            int col = 0;
            for(int k=0;k<n;++k)
            {
                if(j == k)
                {
                    continue;
                }
                d_m[row][col] = d[i][k];
                ++col;
            }
            ++row;
        }
        double sign;
        if(j%2==0)
        {
            sign = 1;
        }
        else
        {
            sign = -1;
        }
        sum += sign * d[0][j] * calc_det(d_m,n-1);
    }
    return sum;
}

int main()
{
    double result;
    double det[MAX][MAX];
    int number;
    scanf("%d",&number);
    for(int i=0;i<number;++i)
    {
        for(int j=0;j<number;++j)
        {
            scanf("%lf",&det[i][j]);
        }
    }
    result = calc_det(det,3);
    printf("%g",result);
    return 0;
}