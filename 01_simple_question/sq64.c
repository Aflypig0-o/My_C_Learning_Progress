#include <stdio.h>
typedef struct 
{
    double width,height;
}Rectangle;

int main()
{
    Rectangle s1;
    scanf("%lf%lf",&s1.width,&s1.height);
    double area = s1.width*s1.height;
    printf("%g",area);
    return 0;
}