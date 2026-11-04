#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

static void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void sift_up(heap *self,int index)
{
    if(self == NULL)
    {
        return;
    }

    while (index > 0 && self->data[index] > self->data[(index-1)/2])
    {
        int parent_index = (index-1) / 2;
        swap(&self->data[index],&self->data[parent_index]);
        index = parent_index;
    }
}

static void sift_down(heap *self,int index)
{
    if(self == NULL)
    {
        return;
    }
    while(index *2+1 < self->size)
    {
        int left_index = index*2+1;
        int right_index = index*2+2;
        int largest_index = index;
        if(left_index < self->size && self->data[left_index] > self->data[largest_index])
        {
            largest_index = left_index;
        }
        if(right_index < self->size && self->data[right_index] > self->data[largest_index])
        {
            largest_index = right_index;
        }
        if(largest_index == index)
        {
            break;
        }
        swap(&self->data[index],&self->data[largest_index]);
        index = largest_index;
    }
}

static void push_impl(heap *self,int val)
{
    if(self == NULL)
    {
        return;
    }
    if(self->size >= self->capacity)
    {
        self->capacity *= 2;
        int *new_data = (int*)realloc(self->data,sizeof(int)*self->capacity);
        if(new_data == NULL)
        {
            perror("realloc");
            return;
        }
        self->data = new_data;
        printf("[系统提示] 堆容量不足，已自动扩容至 %d\n", self->capacity);
    }
    self->data[self->size] = val;
    sift_up(self,self->size);
    self->size++;
}

static int pop_impl(heap *self)
{
    if(self == NULL)
    {
        exit(EXIT_FAILURE);
    }
    if(self->size <= 0)
    {
        fprintf(stderr,"Heap is empty!\n");
        exit(EXIT_FAILURE);
    }
    int max_val = self->data[0];
    self->data[0] = self->data[self->size -1];
    self->size--;
    sift_down(self,0);
    return max_val;
}

static bool is_empty_impl(heap *self)
{
    return self == NULL || self->size == 0;
}

static void destroy_impl(heap *self)
{
    if(self != NULL)
    {
        free(self->data);
        free(self);
    }
}

heap *heap_create(int capacity)
{
    if(capacity <= 0)
    {
        return NULL;
    }
    heap *h = (heap*)malloc(sizeof(heap));
    if(h == NULL)
    {
        perror("malloc");
        return NULL;
    }
    h->capacity = capacity;
    h->data = (int*)malloc(sizeof(int) * h->capacity);
    if(h->data == NULL)
    {
        perror("malloc");
        free(h);
        return NULL;
    }
    h->size = 0;
    h->push = push_impl;
    h->pop = pop_impl;
    h->is_empty = is_empty_impl;
    h->destroy = destroy_impl;
    return h;
}