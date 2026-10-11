#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "infix.h"
#include "tokenize.h"
#include "charstack.h"

bool infix_to_postfix(Token *in, int count, Token *out, int max_out)
{
    if (in == NULL || out == NULL)
    {
        return false;
    }

    Charstack cs;
    charstack_init(&cs);
    int out_count = 0;

    for (int i = 0; i < count; ++i)
    {
        if (in[i].type == TOKEN_NUMBER)
        {
            if (out_count >= max_out)
            {
                return false;
            }
            out[out_count] = in[i];
            ++out_count;
        }
        else if (in[i].type == TOKEN_OP)
        {
            char top;
            while (!charstack_is_empty(&cs) && charstack_peek(&cs, &top) && top != '(' && priority(top) >= priority(in[i].op))
            {
                if (out_count >= max_out)
                {
                    return false;
                }
                charstack_pop(&cs, &top);
                out[out_count].type = TOKEN_OP;
                out[out_count].op = top;
                ++out_count;
            }
            charstack_push(&cs, in[i].op);
        }
        else if (in[i].type == TOKEN_LPAREN)
        {
            charstack_push(&cs, in[i].op);
        }
        else if (in[i].type == TOKEN_RPAREN)
        {
            char top;
            while (charstack_peek(&cs, &top) && top != '(')
            {
                if (out_count >= max_out)
                {
                    return false;
                }
                charstack_pop(&cs, &top);
                out[out_count].type = TOKEN_OP;
                out[out_count].op = top;
                ++out_count;
            }
            if (charstack_is_empty(&cs))
            {
                return false;
            }
            charstack_pop(&cs, &top);
        }
    }

    char top;
    while (!charstack_is_empty(&cs))
    {
        charstack_pop(&cs, &top);
        if (top == '(')
        {
            return false;
        }
        if (out_count >= max_out)
        {
            return false;
        }
        out[out_count].type = TOKEN_OP;
        out[out_count].op = top;
        ++out_count;
    }

    return true;
}
