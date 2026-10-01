#include <stdio.h>
typedef struct
{
    double height,width;
}Rectangle;

void area(Rectangle r,double *area)
{
    *area = r.width * r.height;
}

int main()
{
    double rectangle_area;
    Rectangle r = {3.5,4.0};
    area(r,&rectangle_area);
    printf("%g",rectangle_area);
    return 0;
}