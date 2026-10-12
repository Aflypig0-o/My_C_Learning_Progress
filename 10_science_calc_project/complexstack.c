#include <stdio.h>
#include "complexstack.h"

void complexstack_init(Complexstack *complexstack)
{
    complexstack->top = -1;
}

bool complexstack_is_empty(const Complexstack *complexstack)
{
    return complexstack->top == -1;
}

bool complexstack_is_full(const Complexstack *complexstack)
{
    return complexstack->top == MAX_SIZE -1;
}

bool complexstack_push(Complexstack *complexstack,Complex complex_value)
{
    if(complexstack_is_full(complexstack))
    {
        fprintf(stderr,"Complexstack is full\n");
        return false;
    }
    complexstack->top++;
    complexstack->data[complexstack->top] = complex_value;
    return true;
}

bool complexstack_pop(Complexstack *complexstack,Complex *complex_output)
{
    if(complexstack_is_empty(complexstack))
    {
        fprintf(stderr,"Complexstack is empty\n");
        return false;
    }
    *complex_output = complexstack->data[complexstack->top];
    complexstack->top--;
    return true;
}

bool complexstack_peek(Complexstack *complexstack,Complex *complex_output)
{
    if(complexstack_is_empty(complexstack))
    {
        fprintf(stderr,"Complexstack is empty\n");
        return false;
    }
    *complex_output = complexstack->data[complexstack->top];
    return true;
}
