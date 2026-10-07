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
    CharStack charstack;
    char_stack_init(&charstack);
    int output_index = 0;
    for(int i=0;exper[i] != '\0';++i)
    {
        char token = exper[i];
        if(isspace(token))
        {
            continue;
        }
        if(isdigit(token))
        {
            if(output_index +2 >= output_size)
            {
                return false;
            }
            output[output_index++] = token;
            output[output_index++] = ' ';
        }
        else if(token == '(')
        {
            char_stack_push(&charstack,token);
        }
        else if(token == ')')
        {
            char top;
            while(char_stack_pop(&charstack,top))
            {
                if(top == '(')
                {
                    break;
                }
                output[output_index++] = top;
                output[output_index++] = ' ';
            }
        }
        else if(token == '+' || token == '-' || token == '*' || token == '/')
        {
            char top;
            while(!char_stack_is_empty(&charstack) && char_stack_peek(&charstack,&top) && top != '(' && precedence(top) >= precedence(token))
            {
                char_stack_pop(&charstack,&top);
                output[output_index++] = top;
                output[output_index++] = ' ';
            }
            char_stack_push(&charstack,&token);
        }
        else
        {
            return false;
        }
    }
    char top;
    while(char_stack_pop(&charstack,&top))
    {
        output[output_index++] = top;
        output[output_index++] = ' ';
    }
    output[output_index] = '\0';
    return true;
}