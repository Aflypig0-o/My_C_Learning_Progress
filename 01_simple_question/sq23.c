#include <stdio.h>

int main()
{
    int arr[10] = {0};
    int remnant[10] = {0};
    int count = 0;
    for(int i=0;i<10;++i)
    {
        scanf("%d",&arr[i]);
    }

    remnant[count] = arr[0];
    ++count;

    for(int i=1;i<10;++i)
    {
        if(arr[i]>=remnant[count-1])
        {
            remnant[count] = arr[i];
            ++count;
        }
    }
    for(int i=0;i<count;++i)
    {
        printf("%d ",remnant[i]);
    }
    return 0;
}
