#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "char_stack.h"
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

bool infix_to_postfix(const char *exper,char *output,int output_size)
{
    CharStack stack;
    char_stack_init(&stack);
    int output_index = 0;
    for(output_index;exper[output_index] != '\0';++output_index)
    {
        char token = exper[output_index];
        if(isspace(token))
        {
            continue;
        }
        if(isdigit(token))
        {
            char_stack_push(&stack,token);
        }
        
    }
}