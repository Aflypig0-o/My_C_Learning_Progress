#include <stdio.h>
#include <ctype.h>
#include "stack.h"
#include "postfix_copy.h"

bool eval_postfix(const char *expression,int *result)
{
    Stack s;
    initStack(&s);
    for(int i = 0;expression[i] != '\0';++i)
    {
        if(isspace(expression[i]))
        {
            continue;
        }
        else if(isdigit(expression[i]))
        {
            push(&s,expression[i] - '0');
        }
        else
        {
            int operand1,operand2;
        }
    }
    return true;
}