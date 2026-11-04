#ifndef HEAP_H
#define HEAP_H
#include <stdbool.h>

typedef struct heap
{
    int *data;
    int size;
    int capacity;
    void (*push) (struct heap *self,int val);
    int (*pop) (struct heap *self);
    bool (*is_empty) (struct heap *self);
    void (*destroy) (struct heap *self);
}heap;

heap *heap_create(int capacity);

#endif