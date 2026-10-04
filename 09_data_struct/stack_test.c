#include <stdio.h>
#include "stack.h"

int main()
{
    Stack s;
    initStack(&s);
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    int top;
    peek(&s, &top);
    printf("Top element: %d\n", top);
    int val;
    while (pop(&s, &val)) {
        printf("Popped: %d\n", val);
    }
    printf("Is stack empty? %s\n", isEmpty(&s) ? "Yes" : "No");
    return 0;
}