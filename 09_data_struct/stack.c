#include <stdio.h>
#include "stack.h"

void initStack(Stack* stack) 
{
    stack->top = -1;
}

bool isFull(const Stack* stack) 
{
    return stack->top == MAX_SIZE - 1;
}

bool isEmpty(const Stack* stack) 
{
    return stack->top == -1;
}

bool push(Stack* stack, int value)
{
    if(isFull(stack)) 
    {
        fprintf(stderr, "Stack overflow: cannot push %d\n", value);
        return false;
    }
    ++stack->top;
    stack->data[stack->top] = value;
    return true;
}

bool pop(Stack* stack,int *out)
{
    if(isEmpty(stack)) 
    {
        fprintf(stderr, "Stack underflow: cannot pop\n");
        return false;
    }
    *out = stack->data[stack->top];
    --stack->top;
    return true;
}

bool peek(const Stack* stack, int* out) 
{
    if(isEmpty(stack)) 
    {
        fprintf(stderr, "Stack is empty: cannot peek\n");
        return false;
    }
    *out = stack->data[stack->top];
    return true;
}