#include <stdio.h>

int main()
{
    int n;
    int count = 0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        if(i%3==0||i%5==0)
        {
             printf("%d ",i);
            ++count;
        }
    }
    printf("\n%d",count);
    return 0;
}