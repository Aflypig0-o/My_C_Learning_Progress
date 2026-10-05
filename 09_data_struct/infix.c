#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"
#include "infix.h"

static int precedence(char op)
{
    switch(op)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}