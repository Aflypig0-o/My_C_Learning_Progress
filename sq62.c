#include <stdio.h>
typedef struct {int x,y;} Point;
int main()
{
    Point s1;
    s1.x = 3;
    s1.y = 5;
    printf("(%d,%d)",s1.x,s1.y);
    return 0;
}