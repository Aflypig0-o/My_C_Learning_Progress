#include <stdio.h>
#include "stack.h"

void initStack(Stack* stack) {
    stack->top = -1;
}

bool isFull(const Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

bool isEmpty(const Stack* stack) {
    return stack->top == -1;
}

bool push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack is full\n");
        return false;
    }
    stack->data[++stack->top] = value;
    return true;
}

bool pop(Stack* stack, int* out) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return false;
    }
    *out = stack->data[stack->top--];
    return true;
}

bool peek(Stack* stack, int* out) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return false;
    }
    *out = stack->data[stack->top];
    return true;
}
