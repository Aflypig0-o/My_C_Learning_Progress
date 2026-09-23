#include <stdio.h>

typedef struct
{
    double x,y;
}Point;

int main()
{
    Point s1={0,0};
    Point *p = &s1;
    p -> x = 3;
    p -> y = 4;
    printf("%g %g",s1.x,s1.y);
    return 0;
}