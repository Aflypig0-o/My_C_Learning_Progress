#include <stdio.h>
#include "doublestack.h"

void doublestack_init(Doublestack *doublestack)
{
    doublestack->top = -1;
}

bool doublestack_is_empty(const Doublestack *doublestack)
{
    return doublestack->top == -1;
}

bool doublestack_is_full(const Doublestack *doublestack)
{
    return doublestack->top == MAX_SIZE -1;
}

bool doublestack_push(Doublestack *doublestack,double value)
{
    if(doublestack_is_full(doublestack))
    {
        fprintf(stderr,"Doublestack is full\n");
        return false;
    }
    doublestack->top++;
    doublestack->data[doublestack->top] = value;
    return true;
}

bool doublestack_pop(Doublestack *doublestack,double *output)
{
    if(doublestack_is_empty(doublestack))
    {
        fprintf(stderr,"Doublestack is empty\n");
        return false;
    }
    *output = doublestack->data[doublestack->top];
    doublestack->top--;
    return true;
}

bool doublestack_peek(Doublestack *doublestack,double *output)
{
    if(doublestack_is_empty(doublestack))
    {
        fprintf(stderr,"Doublestack is empty\n");
        return false;
    }
    *output = doublestack->data[doublestack->top];
    return true;
}


