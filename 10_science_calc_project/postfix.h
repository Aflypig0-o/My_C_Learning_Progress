#ifndef POSTFIX_H
#define POSTFIX_H
#include <stdbool.h>
#include "tokenize.h"

/*
 * eval_postfix —— 计算后缀表达式（逆波兰表达式）的值
 *
 * 功能：
 *     遍历后缀 Token 数组，数字压栈，运算符弹两个操作数计算后压回栈。
 *     最终栈顶就是结果。
 *
 * 举例：
 *     Token 数组: [3] [+] [4] [2] [*]  →  3 + (4 * 2) = 11
 *     Token 数组: [3] [4] [+] [2] [*]  →  (3 + 4) * 2 = 14
 *
 * 参数：
 *     postfix - 后缀表达式 Token 数组（infix_to_postfix 的输出）
 *     count   - postfix 数组里有效 Token 的个数
 *     result  - 输出参数，存放计算结果
 *
 * 返回：
 *     true  - 计算成功，result 里存好了结果
 *     false - 出错（操作数不足、除零、非法运算符等）
 */
bool eval_postfix(Token *postfix, int count, double *result);

#endif