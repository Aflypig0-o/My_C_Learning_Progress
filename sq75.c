#include <stdio.h>
typedef struct
{
    double width,height;
}Rectangle;

void multiply_factor(Rectangle *rec,double factor)
{
    rec->width *= factor;
    rec->height *= factor;
}

int main()
{
    Rectangle r = {3.0,4.0};
    double factor = 2.0;
    printf("%g * %g\n",r.width,r.height);
    multiply_factor(&r,factor);
    printf("%g * %g",r.width,r.height);
    return 0;
}