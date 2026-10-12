#include <stdio.h>
#include <math.h>
#include "doublestack.h"
#include "postfix.h"

bool eval_postfix(Token *postfix, int count, double *result)
{
    // 参数合法性检查
    if (postfix == NULL || result == NULL)
    {
        return false;
    }

    // 创建一个双精度浮点栈，用来存放操作数和中间结果
    Doublestack ds;
    doublestack_init(&ds);

    // 从左到右逐个扫描 Token
    for (int i = 0; i < count; ++i)
    {
        // ================================================================
                // 情况1：当前 Token 是数字（TOKEN_NUMBER）
        // ================================================================
        // 数字直接压栈，等运算符来的时候再弹出来计算
        if (postfix[i].type == TOKEN_NUMBER)
        {
            doublestack_push(&ds, postfix[i].value);
        }

        // ================================================================
        // 情况2：当前 Token 是运算符（type == 1）
        // ================================================================
        // 弹出栈顶两个操作数：
        //   先弹的是右操作数（operand2）
        //   后弹的是左操作数（operand1）
        // 计算结果压回栈
        else
        {
            double operand2, operand1;
            if (!doublestack_pop(&ds, &operand2) || !doublestack_pop(&ds, &operand1))
            {
                // 栈里操作数不足，表达式不合法
                fprintf(stderr, "Not enough operands\n");
                return false;
            }

            double result_value;
            switch (postfix[i].op)
            {
                case '+':
                    result_value = operand1 + operand2;
                    break;
                case '-':
                    result_value = operand1 - operand2;
                    break;
                case '*':
                    result_value = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0.0)
                    {
                        fprintf(stderr, "Division by zero\n");
                        return false;
                    }
                    result_value = operand1 / operand2;
                    break;
                case '^':
                    result_value = pow(operand1,operand2);
                    break;
                default:
                    fprintf(stderr, "Invalid operator\n");
                    return false;
            }

            // 计算结果压回栈，等后面的运算符来用
            doublestack_push(&ds, result_value);
        }
    }

    // 全部扫描完毕，栈里应该只剩一个值，那就是最终结果
    if (!doublestack_pop(&ds, result))
    {
        // 栈空了说明表达式不合法
        fprintf(stderr, "No result in stack\n");
        return false;
    }
    //检查是否空栈
    if(!doublestack_is_empty(&ds))
    {
        fprintf(stderr,"Extra operands in stack\n");
        return false;
    }
    return true;
}