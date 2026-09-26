#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);
    int *count =(int*)calloc(10,sizeof(int));
    if(count == NULL)
    {
        return 1;
    }
    for(int i=0;i<n;++i)
    {
        int x;
        scanf("%d",&x);
        if(x >=10 || x<0)
        {
            printf("unexpected input");
            free(count);
            return 0;
        }
        ++count[x];
    }

    for(int i=0;i<10;++i)
    {
        if(count[i] == 0)
        {
            continue;
        }
        printf("数字%d一共出现了%d次\n",i,count[i]);
    }
    free(count);
    count = NULL;
    return 0;
}