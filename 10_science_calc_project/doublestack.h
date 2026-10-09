#ifndef Doublestack_H
#define Doublestack_H
#define MAX_SIZE 100
#include <stdbool.h>

typedef struct
{
    double data[MAX_SIZE];
    int top;
}Doublestack;

void Doublestack_init(Doublestack *Doublestack);
bool Doublestack_is_empty(const Doublestack *Doublestack);
bool Doublestack_is_full(const Doublestack *Doublestack);
bool Doublestack_push(Doublestack *Doublestack,int value);
bool Doublestack_pop(Doublestack *Doublestack,int *output);
bool Doublestack_peek(Doublestack *Doublestack,int *output);

#endif