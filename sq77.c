#include <stdio.h>
typedef struct
{
    int x,y;
}Point;

Point make_point (int x,int y)
{
    Point p = {x,y};
    return p;
}

int main()
{
    Point point = make_point(3,4);
    printf("%d %d",point.x,point.y);
    return 0;
}