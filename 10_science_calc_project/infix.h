#ifndef INFIX_H
#define INFIX_H
#include <stdbool.h>
#include "tokenize.h"

/*
 * infix_to_postfix —— 中缀表达式转后缀表达式（调度场算法）
 *
 * 功能：
 *     把 tokenize 输出的中缀 Token 数组，转换成后缀（逆波兰）Token 数组。
 *     转换过程中括号被去掉，运算符按优先级重新排列。
 *
 * 举例：
 *     中缀：3 + 4 * 2       →  后缀：3 4 2 * +
 *     中缀：(3 + 4) * 2     →  后缀：3 4 + 2 *
 *
 * 参数：
 *     in        - 中缀 Token 数组（tokenize 的输出）
 *     count     - in 数组里有效 Token 的个数
 *     out       - 输出的后缀 Token 数组（调用者分配，容量 >= max）
 *     max       - out 数组的容量上限（防止越界）
 *     out_count - 输出参数，返回后缀数组里有效 Token 的个数
 *
 * 返回：
 *     true  - 转换成功
 *     false - 出错（括号不匹配、输出数组太小等）
 */
bool infix_to_postfix(Token *in, int count, Token *out, int max, int *out_count);

#endif