#ifndef CHAR_STACK_H
#define CHAR_STACK_H
#define MAX_SIZE 100

#include <stdbool.h>

typedef struct {
    char data[MAX_SIZE];
    int top;
} CharStack;

void char_stack_init(CharStack *stack);
bool char_stack_push(CharStack *stack, char c);
bool char_stack_pop(CharStack *stack, char *c);
bool char_stack_is_empty(CharStack *stack);
bool char_stack_is_full(CharStack *stack);
bool char_stack_peek(const CharStack *stack, char *c);

#endif // CHAR_STACK_H