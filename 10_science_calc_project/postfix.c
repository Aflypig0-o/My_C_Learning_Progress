#include <stdio.h>
#include <ctype.h>
#include "doublestack.h"
#include "postfix.h"

bool eval_postfix(const char *expression,double *result)
{
    Doublestack s;
    Doublestack_init(&s);
    for(int i=0;expression[i] != '\0';++i)
    {
        if(isspace(expression[i]))
        {
            continue;
        }
        else if(isdigit(expression[i]))
        {
            Doublestack_push(&s,expression[i] - '0');
        }
        else
        {
            double operand2,operand1;
            if(!Doublestack_pop(&s,&operand2) || !Doublestack_pop(&s,&operand1))
            {
                return false;//数量不足以计算
            }
            int result_value;
            switch(expression[i])
            {
                case '+' : result_value = operand1 + operand2;break;
                case '-' : result_value = operand1 - operand2;break;
                case '*' : result_value = operand1 * operand2;break;
                case '/' : 
                if(operand2 == 0.0)
                {
                    fprintf(stderr,"Maths mistake");//0不可以做除数
                    return false;
                }
                result_value = operand1 / operand2;
                break;
                default:fprintf(stderr,"Invalid operator");return false;
            }
            Doublestack_push(&s,&result_value);
        }
    }
    if(!pop(&s,result))
    {
        return false;//栈里没有结果
    }
    return true;
}
