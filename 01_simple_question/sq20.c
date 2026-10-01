#include <stdio.h>

int main()
{
    int a[5] = {0};
    int b[5] = {0};
    printf(" ‰»Î:");
    for(int i=0;i<5;++i)
    {
        scanf("%d",&a[i]);
    }
    printf(" ‰≥ˆ:");
    for(int i=0;i<5;++i)
    {
        b[i] = a[i];
        printf("%d ",b[i]);
    }
    return 0;
}