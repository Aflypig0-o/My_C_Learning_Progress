#include <stdio.h>
#include <stdbool.h>

int main()
{
    int arr[10] = {0};
    printf("请输入十个整数:");
    for(int i=0;i<10;++i)
    {
        scanf("%d",&arr[i]);
    }
    printf("去重后:");
    for(int i=0;i<10;++i)
    {
        bool is_duplicate = false;
        for(int j=0;j<i;++j)
        {
            if(arr[i] == arr[j])
            {
                is_duplicate = true;
                break;
            }
        }
        if(is_duplicate == false)
        {
            printf("%d ",arr[i]);
        }
    }
    return 0;
}