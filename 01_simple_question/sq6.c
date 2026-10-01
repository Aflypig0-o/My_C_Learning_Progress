#include <stdio.h>

void move_left(int *a,int *b,int *c)
{
    int temp1 =*c;
    int temp2 =*b;
    *c = *a;
    *a = temp2;
    *b = temp1;
}

int main()
{
    int x,y,z;
    scanf("%d%d%d",&x,&y,&z);
    move_left(&x,&y,&z);
    printf("%d %d %d",x,y,z);
    return 0;
}