#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "setting.h"
#include "basic_calc.h"
#include "infix.h"
#include "postfix.h"

bool handle_basic_calc(char *expression,Token *token_in,Token *token_out,double *result)
{
    int token_count = 0;

    if(!tokenize(expression,token_in,g_setting.max_token,&token_count))
    {
        return false;
    }

    int postfix_count = 0;

    if(!infix_to_postfix(token_in,token_count,token_out,g_setting.max_token,&postfix_count))
    {
        return false;
    }

    if(!eval_postfix_basic(token_out,postfix_count,result))
    {
        return false;
    }
    return true;
}