#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "tokenize.h"

/*
 * priority —— 返回运算符的优先级
 *
 * 优先级越高，越先计算（在后缀表达式中越先出现）。
 *
 * 返回值：
 *     1 - 加减法（+ -）
 *     2 - 乘除法（* /）
 *     3 - 幂运算（^）
 *     0 - 不是运算符
 */
int priority(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

/*
 * is_op —— 判断字符是否为运算符
 *
 * 支持的运算符：+ - * / ^
 * 注意：'-' 既可以是负号（一元），也可以是减号（二元），
 * 这里统一返回 true，具体语义由 tokenize 根据上下文判断。
 */
bool is_op(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

/*
 * tokenize —— 把表达式字符串拆分成 Token 数组
 *
 * 功能：
 *     扫描输入字符串，识别数字（含负数）、运算符、左右括号，
 *     逐个填入 token 数组。
 *
 * 识别规则：
 *     数字   - 连续的数字和小数点，如 "3.14"、"42"
 *     负数   - 表达式开头、运算符后、左括号后的 '-' 视为负号
 *     运算符 - + - * / ^
 *     左括号 - (
 *     右括号 - )
 *     空格   - 跳过
 *
 * 参数：
 *     s         - 输入表达式字符串
 *     token     - 输出的 Token 数组（调用者提前分配好空间）
 *     max_token - token 数组的容量上限（防止越界）
 *     c         - 输出参数，返回实际生成的 Token 个数
 *
 * 返回：
 *     true  - 解析成功
 *     false - 出错（非法字符、数组溢出、内存分配失败等）
 */
bool tokenize(char *s, Token *token, int max_token, int *c)
{
    // 参数合法性检查（必须在 strlen 之前，否则 s 为 NULL 会崩溃）
    if (s == NULL || token == NULL || c == NULL)
    {
        return false;
    }

    int count = 0;       // 已生成的 Token 个数
    int len = strlen(s); // 字符串长度
    int i = 0;           // 当前扫描位置
    while(i < len)
    {
        if(s[i] == '-' && (count == 0 || token[count-1].type == TOKEN_OP || token[count-1].type == TOKEN_LPAREN))//判断是否为负数，并手动构建负数字符串
        {
            ++i;//跳过'-'，让下面的分支把负号带上
            int start = i;
            while(i<len && (isdigit(s[i]) || s[i] == '.'))
            {
                ++i;//到数字结束位置
            }
            int n = i-start;
            if(n == 0)
            {
                fprintf(stderr,"Expected number after unary '-'\n");//处理'-'后没有数字的意外输入
                return false;
            }
            char *buf = (char*)malloc(n+2);//多1字节给负号
            if(buf == NULL)
            {
                perror("malloc");
                return false;
            }
            buf[0] = '-';//存储负号
            memcpy(buf+1,s+start,n);
            buf[n+1] = '\0';
            if(count >= max_token)
            {
                free(buf);
                fprintf(stderr,"Token array overflow\n");
                return false;
            }
            token[count].type = TOKEN_NUMBER;
            token[count].value = strtod(buf,NULL);
            ++count;
            free(buf);//释放内存防止泄露
            continue;
        }
        if(s[i] == ' ')
        {
            ++i;
            continue;//跳过空格
        }
        if(isdigit(s[i]) || s[i] =='.')//判断数字和小数点
        {
            int start = i;//记录数字开始位置
            while(i<len && (isdigit(s[i]) || s[i] == '.'))
            {
                ++i;//到数字结束位置为止，包括小数点
            }
            int n = i-start;//一共多少位
            char *buf = (char*)malloc((n+1)*sizeof(char));//此处分配n+1，防止越界写入
            if(buf == NULL)
            {
                perror("malloc");
                return false;
            }
            memcpy(buf,s+start,n);
            buf[n] = '\0';
            if(count >= max_token)
            {
                free(buf);
                fprintf(stderr,"Token array overflow\n");
                return false;
            }
            token[count].type = TOKEN_NUMBER;//是数字
            token[count].value = strtod(buf,NULL);
            ++count;
            free(buf);//释放内存防止泄露
            continue;
        }
        if(is_op(s[i]))//判断运算符
        {
             if(count >= max_token)
            {
                fprintf(stderr, "Token array overflow\n");
                return false;
            }   
            token[count].type = TOKEN_OP;
            token[count].op = s[i];
            ++count;
            ++i;
            continue;
        }
        if(s[i] == '(')//判断左括号
        {
            if(count >= max_token)
            {
                fprintf(stderr, "Token array overflow\n");
                return false;
            } 
            token[count].type = TOKEN_LPAREN;
            token[count].op = s[i];
            ++count;
            ++i;
            continue;
        }
        if(s[i] == ')')//判断右括号
        {
            if(count >= max_token)
            {
                fprintf(stderr, "Token array overflow\n");
                return false;
            } 
            token[count].type = TOKEN_RPAREN;
            token[count].op = s[i];
            ++count;
            ++i;
            continue;
        }
        fprintf(stderr,"Unexpected input: %c\n",s[i]);
        return false;
    }
    *c = count;//传递Token数
    return true;
}