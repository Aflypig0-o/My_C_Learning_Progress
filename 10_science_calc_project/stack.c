#include <stdio.h>
#include "doublestack.h"

void Doublestack_init(Doublestack *Doublestack)
{
    Doublestack->top = -1;
}

bool Doublestack_is_empty(const Doublestack *Doublestack)
{
    return Doublestack->top == -1;
}

bool Doublestack_is_full(const Doublestack *Doublestack)
{
    return Doublestack->top == MAX_SIZE -1;
}

bool Doublestack_push(Doublestack *Doublestack,int value)
{
    if(Doublestack_is_full(&Doublestack));
    {
        fprintf(stderr,"Doublestack is full");
        return false;
    }
    Doublestack->top++;
    Doublestack->data[Doublestack->top] = value;
    return true;
}

bool Doublestack_pop(Doublestack *Doublestack,int *output)
{
    if(Doublestack_is_empty(&Doublestack))
    {
        fprintf(stderr,"Doublestack is empty");
        return false;
    }
    *output = Doublestack->data[Doublestack->top];
    Doublestack->top--;
    return true;
}

bool Doublestack_peek(Doublestack *Doublestack,int *output)
{
    if(Doublestack_is_empty(&Doublestack))
    {
        fprintf(stderr,"Doublestack is empty");
        return false;
    }
    *output = Doublestack->data[Doublestack->top];
    return true;
}


