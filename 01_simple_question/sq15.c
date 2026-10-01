#include <stdio.h>

int main()
{
    int arr[5] = {0};
    int max,max_index;
    for(int i=0;i<5;++i)
    {
        scanf("%d",&arr[i]);
    }
        max = arr[0];
        max_index = 1;
    for(int i=0;i<5;++i)
    {
        if (arr[i] > max)
        {
            max = arr[i];
            max_index = i+1;           
        }
    }
    
    printf("最大值为:%d\n",max);


    for(int i=0;i<5;++i)
    {
        if(arr[i] == max)
        printf("出现在第%d个数字\n",i+1);
    }
    return 0;
}