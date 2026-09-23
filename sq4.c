#include <stdio.h>

void sort_desc(int *a,int*b)
{
    if(*a < *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}
int main()
{
    int x,y;
    scanf("%d%d",&x,&y);
    sort_desc(&x,&y);
    printf("%d%d",x,y);
    return 0;
}