#include <stdio.h>

double det_3(double m[3][3])
{
    double d = 0;
    double positive = m[0][0]*m[1][1]*m[2][2] + m[0][1]*m[1][2]*m[2][0] + m[1][0]*m[2][1]*m[0][2];
    double negative = -(m[0][2]*m[1][1]*m[2][0]+m[0][1]*m[1][0]*m[2][2]+m[0][0]*m[2][1]*m[1][2]);
    d = positive + negative;
    return d;
}

int main()
{
    double result = 0;
    double mat[3][3] = {0};
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<3;++j)
        {
            scanf("%lf",&mat[i][j]);
        }
    }
    result = det_3(mat);
    printf("%g",result);
    return 0;
}