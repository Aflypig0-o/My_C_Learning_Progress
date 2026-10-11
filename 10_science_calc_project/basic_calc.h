#ifndef BASIC_CALC_H
#define BASIC_CALC_H
#include <stdbool.h>
#include "tokenize.h"

/*
 * handle_basic_calc —— 基础四则运算的完整流程
 *
 * 功能：
 *     1. tokenize：把表达式字符串拆成 Token 数组
 *     2. infix_to_postfix：中缀转后缀（调度场算法）
 *     3. eval_postfix：计算后缀表达式的值
 *
 * 参数：
 *     expression - 用户输入的表达式字符串
 *     token_in   - 中缀 Token 数组（调用者分配，容量 >= g_setting.max_token）
 *     token_out  - 后缀 Token 数组（调用者分配，容量 >= g_setting.max_token）
 *     result     - 输出参数，存放计算结果
 *
 * 返回：
 *     true  - 计算成功，result 里存好了结果
 *     false - 任一步骤失败（解析错误、括号不匹配、除零等）
 */
bool handle_basic_calc(char *expression, Token *token_in, Token *token_out, double *result);

#endif