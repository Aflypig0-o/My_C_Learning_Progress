#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack* stack);
bool isFull(const Stack* stack);
bool isEmpty(const Stack* stack);
bool push(Stack* stack, int value);
bool pop(Stack* stack, int* out);
bool peek(Stack* stack, int* out);

#endif // STACK_H