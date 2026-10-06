#ifndef STACK.H
#define STACK.H
#define MAX_SIZE 100
#include <stdbool.h>

typedef struct
{
    int data[MAX_SIZE];
    int top;
}Stack;

void stack_init(Stack *stack);
bool stack_is_full(const Stack *stack);
bool stack_is_empty(const Stack *stack);
bool stack_push(Stack *stack,int value);
bool stack_pop(Stack *stack,int *output);
bool stack_peek(const Stack *stack,int *output);
#endif