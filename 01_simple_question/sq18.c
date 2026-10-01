#include <stdio.h>
#include <stdbool.h>

int main()
{
    bool find_key = false;
    int arr[8] = {0};
    int key;
    int arr_index = 0;
    printf("输入:");
    for(int i=0;i<8;++i)
    {
        scanf("%d",&arr[i]);
    }
    printf("查找:");
    scanf("%d",&key);
    for(int i=0;i<8;++i)
    {
        if(arr[i] == key)
        {
            arr_index = i+1;
            printf("%d在第%d个",key,arr_index);
            find_key = true;
            break;
        }
    }
    if(find_key == false)
    {
        printf("未找到");
    }
    return 0;
}