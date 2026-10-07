#include <stdio.h>
#include "stack_copy.h"

void stack_init(Stack *stack)
{
    stack->top = -1;
}

bool stack_is_empty(const Stack *stack)
{
    return stack->top == -1;
}

bool stack_is_full(const Stack *stack)
{
    return stack->top == MAX_SIZE -1;
}

bool stack_push(Stack *stack,int value)
{
    if(stack_is_full(&stack))
    {
        fprintf(stderr,"Full");
        return false;
    }
    stack->data[stack->top++] = value;
    return true;
}

bool stack_pop(Stack *stack,int *output)
{
    if(stack_is_empty(&stack))
    {
        fprintf(stderr,"Empty");
        return false;
    }
    *output = stack->data[stack->top];
    stack->top--;
    return true;
}

bool stack_peek(Stack *stack,int *output)
{
    if(stack_is_empty(&stack))
    {
        fprintf(stderr,"Empty");
        return false;
    }
    *output = stack->data[stack->top];
    return true;
}
