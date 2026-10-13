#ifndef TOKENIZE_H
#define TOKENIZE_H
#include <stdbool.h>

/*
 * TokenType —— Token 的类型枚举
 *
 * 用枚举代替裸数字，让代码可读性更好：
 *   TOKEN_NUMBER  数字（如 3.14、-5）
 *   TOKEN_OP      运算符（+ - * / ^）
 *   TOKEN_LPAREN  左括号 (
 *   TOKEN_RPAREN  右括号 )
 */
typedef enum
{
    TOKEN_NUMBER,   // 数字
    TOKEN_OP,       // 运算符
    TOKEN_LPAREN,   // 左括号
    TOKEN_RPAREN,    // 右括号
    TOKEN_IM //虚数
} TokenType;

/*
 * Token —— 表达式中的一个词法单元
 *
 * 一个 Token 要么是数字，要么是运算符/括号。
 * value 字段只在 type == TOKEN_NUMBER 时有效。
 * op 字段只在 type == TOKEN_OP / TOKEN_LPAREN / TOKEN_RPAREN 时有效。
 */
typedef struct
{
    TokenType type;   // Token 的类型
    double value;     // 仅 TOKEN_NUMBER 有效
    char op;          // 仅 TOKEN_OP / TOKEN_LPAREN / TOKEN_RPAREN 有效
} Token;

int priority(char op);
bool is_op(char c);
bool tokenize(char *s, Token *token, int max_token, int *c);

#endif