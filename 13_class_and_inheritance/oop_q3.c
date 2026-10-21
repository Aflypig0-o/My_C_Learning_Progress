#include <stdio.h>
#include <stdlib.h>

typedef struct DynArray
{
    int *data;
    int size;
    int capacity;
    void (*push_back)(struct DynArray *self, int val);
    void (*free_array) (struct DynArray *self);
}DynArray;

static void push_back_impl(struct DynArray *self,int val)
{
    if(self->size >= self->capacity)
    {
        int new_capacity = 2 * self->capacity;
        int *new_data = (int*)realloc(self->data,new_capacity*sizeof(int));
        if(new_data == NULL)
        {
            perror("malloc");
            return;
        }
        self->data = new_data;
        self->capacity = new_capacity;
    }
    self->data[self->size] = val;
    self->size++; 
}

static void free_array_impl(struct DynArray *self)
{
    if(self == NULL)
    {
        return;
    }
    free(self->data);
    free(self);
}

DynArray *create()
{
    DynArray *arr = (DynArray*)malloc(1 *sizeof(DynArray));
    if(arr == NULL)
    {
        perror("malloc");
        return NULL;
    }
    arr->size = 0;
    arr->capacity = 4;
    arr->data = (int*)malloc(arr->capacity*sizeof(int));
    if(arr->data == NULL)
    {
        perror("malloc");
        free(arr);
        return NULL;
    }
    arr->push_back = push_back_impl;
    arr->free_array = free_array_impl;
    return arr;
}


int main()
{
     DynArray *arr = create();
    
    // 塞入 10 个数据，测试自动扩容
    for (int i = 0; i < 10; i++) {
        arr->push_back(arr, i * 10);
    }
    
    printf("数组内容: ");
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n数组容量: %d\n", arr->capacity); // 应该扩容到了 16
    
    arr->free_array(arr); // 销毁数组
    return 0;
}