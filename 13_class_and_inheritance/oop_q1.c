#include <stdio.h>
#include <stdlib.h>

typedef struct Counter
{
    int count;
    void (*increment) (struct Counter *self);
    int (*get_value) (struct Counter *self);
}Counter;

static void increment_impl(struct Counter *self)
{
    self->count++;
}

static int get_value_input(struct Counter *self)
{
    return self->count;
}

Counter *create(int initial)
{
    Counter *c = (Counter*)malloc(sizeof(Counter));
    if(c == NULL)
    {
        perror("malloc");
        return NULL;
    }
    c->count = initial;
    c->increment = increment_impl;
    c->get_value = get_value_input;
    return c;
}

int main()
{
    Counter *c = create(10);
    c->increment(c);
    c->increment(c);
    printf("当前值: %d\n", c->get_value(c)); // 预期输出 12
    free(c);
    return 0;
}