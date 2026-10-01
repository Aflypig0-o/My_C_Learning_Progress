#include <stdio.h>
typedef struct
{
    double width,height;
}Rectangle;

void init_rect(Rectangle *r,double w,double h)
{
    r->width = w;
    r->height = h;
}

int main()
{
    Rectangle rect;
    init_rect(&rect,3.0,4.0);
    printf("宽%g,高%g",rect.width,rect.height);
    return 0;
}