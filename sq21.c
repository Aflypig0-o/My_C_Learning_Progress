#include <stdio.h>
#include <stdbool.h>

void bubble_sort(int arr[],int len)
{
    for(int i=0;i<len -1;++i)
    {
        bool swapped = false;
        for(int j=0;j<len -1-i;++j)
        {
            if(arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = true;
            }
        }
        if(swapped == false)
        {
            break;
        }
    }
}
int main()
{
    int arr[5] = {0};
    printf("请输入5个整数:");
    for(int i=0;i<5;++i)
    {
        scanf("%d",&arr[i]);
    }
    bubble_sort(arr,5);
    printf("排序后:");
    for(int i=0;i<5;++i)
    {
        printf("%d ",arr[i]);
    }

    return 0;
}