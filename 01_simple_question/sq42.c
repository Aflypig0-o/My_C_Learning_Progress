#include <stdio.h>

static int call_count = 0;

void func()
{
    ++call_count;
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        func();
    }
    printf("%d",call_count);
    return 0;
}