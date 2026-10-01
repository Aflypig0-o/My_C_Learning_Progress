#include <stdio.h>

int next_id()
{
    static int id=0;
    ++id;
    return id;
}

int main()
{
    for(int i=0;i<5;++i)
    {
        printf("%d ",next_id());
    }
    return 0;
}