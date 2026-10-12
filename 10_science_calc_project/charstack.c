#include <stdio.h>
#include "charstack.h"

void charstack_init(Charstack *charstack)
{
    charstack->top = -1;
}

bool charstack_is_empty(const Charstack *charstack)
{
    return charstack->top == -1;
}

bool charstack_is_full(const Charstack *charstack)
{
    return charstack->top == MAX_SIZE -1;
}

bool charstack_push(Charstack *charstack,char op)
{
    if(charstack_is_full(charstack))
    {
        fprintf(stderr,"Stack is full\n");//栈满无法压栈
        return false;
    }
    charstack->top++;
    charstack->data[charstack->top] = op;
    return true;
}

bool charstack_pop(Charstack *charstack,char *out)
{
    if(charstack_is_empty(charstack))
    {
        fprintf(stderr,"Stack is empty\n");//栈空无法弹出
        return false;
    }
    *out = charstack->data[charstack->top];
    charstack->top--;
    return true;
}

bool charstack_peek(const Charstack *charstack,char *out)
{
    if(charstack_is_empty(charstack))
    {
        fprintf(stderr,"Stack is empty\n");//栈空无法看栈顶
        return false;
    }
    *out = charstack->data[charstack->top];
    return true;
}