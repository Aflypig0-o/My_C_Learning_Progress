#include <stdio.h>

typedef struct
{
    int data[100];
    int size;
}IntArray;

void init(IntArray *arr)
{
    arr->size = 0;
}

void push_back(IntArray *arr,int value)
{
    arr->data[arr->size] = value;
    ++arr->size;
}

void print(IntArray *arr)
{
    for(int i=0;i<(arr->size);++i)
    {
        printf("%d ",arr->data[i]);
    }
    printf("\n");
}

int calc_sum(const IntArray *arr)
{
    int sum = 0;
    for(int i=0;i<arr->size;++i)
    {
        sum += arr->data[i];
    }
    return sum;
}

int main()
{
    IntArray arr;
    init(&arr);
    for(int i=0;i<5;++i)
    {
        int x;
        scanf("%d",&x);
        push_back(&arr,x);
    }
    printf("数组\n");
    print(&arr);
    printf("和: %d\n",calc_sum(&arr));
    return 0;
}