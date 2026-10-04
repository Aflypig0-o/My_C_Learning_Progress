#include <stdio.h>
#include <ctype.h>
#include "postfix.h"
#include "stack.h"

bool eval_postfix(const char *expression, int *result)
{
    Stack s;
    initStack(&s);
    for (int i = 0; expression[i] != '\0' ;++i)
    {
        if (isspace(expression[i]))
        {
            continue; // Skip whitespace
        }
        else if(isdigit(expression[i]))
        {
            push(&s, expression[i] - '0'); // Convert char to int and push onto stack
        }
        else
        {
            int operand2, operand1;
            if (!pop(&s, &operand2) || !pop(&s, &operand1))
            {
                return false; // Not enough operands
            }
            int resultValue;
            switch (expression[i])
            {
                case '+':
                    resultValue = operand1 + operand2;
                    break;
                case '-':
                    resultValue = operand1 - operand2;
                    break;
                case '*':
                    resultValue = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0)
                    {
                        return false; // Division by zero
                    }
                    resultValue = operand1 / operand2;
                    break;
                default:
                    return false; // Invalid operator
            }
            push(&s, resultValue);
        }
    }
    if (!pop(&s, result))
    {
        return false; // No result on stack
    }
    return true;
}

