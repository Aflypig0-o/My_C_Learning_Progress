#include <stdio.h>
typedef struct
{
    
    double x,y;
}Point;

void print_point(Point p)
{
    printf("%g %g",p.x,p.y);
    p.x = 6.0;
    p.y = 8.0;
    printf("%g %g",p.x,p.y);
}

int main()
{
    Point s1 = {3.0,4.0};
    print_point(s1);
    printf("%g %g",s1.x,s1.y);
    return 0;
}