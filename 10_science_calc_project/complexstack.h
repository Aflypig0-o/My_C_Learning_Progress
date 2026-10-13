#ifndef COMPLEXSTACK_H
#define COMPLEXSTACK_H
#define MAX_SIZE 100
#include <stdbool.h>
#include "complex.h"

typedef struct
{
    Complex data[MAX_SIZE];
    int top;
}Complexstack;

void complexstack_init(Complexstack *complexstack);
bool complexstack_is_empty(const Complexstack *complexstack);
bool complexstack_is_full(const Complexstack *complexstack);
bool complexstack_push(Complexstack *complexstack,Complex complex_value);
bool complexstack_pop(Complexstack *complexstack,Complex *complex_output);
bool complexstack_peek(Complexstack *complexstack,Complex *complex_output);

#endif