#include <stdio.h>
#include "cqueue.h"

static bool enqueue_impl(CQueue *self,int val)
{
    if(self == NULL || self->is_full(self))
    {
        fprintf(stderr,"Error\n");
        return false;
    }
    self->data[self->rear] = val;
    self->rear = (self->rear + 1) % self->capacity;
    return true;
}

static bool dequeue_impl(CQueue *self,int *out_val)
{
    if(self == NULL || self->is_empty(self))
    {
        fprintf(stderr,"Error\n");
        return false;
    }
    *out_val = self->data[self->front];
    self->front = (self->front + 1) % self->capacity;
    return true;
}

static bool is_empty_impl(CQueue *self)
{
    if(self == NULL)
    {
        fprintf(stderr,"ERROR\n");
        return true;
    }
    return self->front == self->rear;
}

static bool is_full_impl(CQueue *self)
{
    if(self == NULL)
    {
        fprintf(stderr,"ERROR\n");
        return false;
    }
    return (self->rear + 1 ) % self->capacity == self->front;
}

static int get_front_impl(CQueue *self)
{
    if(self == NULL || self->front == self->rear)
    {
        return -1;
    }
    return self->data[self->front];
}

static int get_rear_impl(CQueue *self)
{
    if(self == NULL || self->front == self->rear)
    {
        return -1;
    }
    int real_index;
    real_index = (self->rear - 1 + self->capacity) % self->capacity;
    return self->data[real_index];
}

static void destroy_impl(CQueue *self)
{
    if(self == NULL)
    {
        return;
    }
    free(self->data);
    free(self);
}

CQueue *cqueue_create(int k)
{
    if(k <= 0)
    {
        fprintf(stderr,"Error\n");
        return NULL;
    }
    CQueue *cqueue = (CQueue*)malloc(sizeof(CQueue));
    
    if(cqueue == NULL)
    {
        perror("malloc");
        return NULL;
    }
    cqueue->capacity = k+1;
    cqueue->data = (int*)malloc(sizeof(int) * cqueue->capacity);
    if(cqueue->data == NULL)
    {
        perror("malloc");
        free(cqueue);
        return NULL;
    }
    cqueue->front = 0;
    cqueue->rear = 0;
    cqueue->enqueue = enqueue_impl;
    cqueue->dequeue = dequeue_impl;
    cqueue->is_empty = is_empty_impl;
    cqueue->is_full = is_full_impl;
    cqueue->get_front = get_front_impl;
    cqueue->get_rear = get_rear_impl;
    cqueue->destroy = destroy_impl;
    return cqueue;
}