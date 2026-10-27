#include <stdio.h>
#include "cqueue.h"

static bool enqueue_impl(CQueue *self,int val)
{
    if(self == NULL || self->is_full(self))
    {
        fprintf(stderr,"Error\n");
        return false;
    }
    
}

static bool is_empty_impl(CQueue *self)
{
    if(self == NULL)
    {
        fprintf(stderr,"ERROR\n");
        return false;
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
CQueue *cqueue_create(int k)
{
    CQueue *cqueue = (CQueue*)malloc(sizeof(CQueue));
    if(cqueue == NULL)
    {
        perror("malloc");
        return NULL;
    }
    cqueue->capacity = k+1;
}