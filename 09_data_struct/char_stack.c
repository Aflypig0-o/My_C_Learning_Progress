#include <stdio.h>
#include "char_stack.h"

void char_stack_init(CharStack *stack)
{
    stack->top = -1;
}

bool char_stack_is_full(const CharStack *stack)
{
    return stack->top == MAX_SIZE - 1;
}

bool char_stack_is_empty(const CharStack *stack)
{
    return stack->top == -1;
}

bool char_stack_push(CharStack *stack, char c)
{
    if (char_stack_is_full(stack)) 
    {
        fprintf(stderr, "CharStack overflow: cannot push '%c'\n", c);
        return false;
    }
    stack->data[++stack->top] = c;
    return true;
}

bool char_stack_pop(CharStack *stack, char *c)
{
    if (char_stack_is_empty(stack)) 
    {
        fprintf(stderr, "CharStack underflow: cannot pop\n");
        return false;
    }
    *c = stack->data[stack->top--];
    return true;
}

bool char_stack_peek(const CharStack *stack,char *c)
{
    if(char_stack_is_empty(stack)) 
    {
        fprintf(stderr, "CharStack is empty: cannot peek\n");
        return false;
    }
    *c = stack->data[stack->top];
    return true;
}