#ifndef CHARSTACK_H
#define CHARSTACK_H
#include <stdbool.h>

/*
 * ============================================================
 *  charstack.h —— 字符栈
 * ============================================================
 *  用途：
 *      在 infix_to_postfix（调度场算法）中临时存放运算符和左括号。
 *      运算符在这里"排队"，等到时机成熟才输出。
 *
 *  容量：固定 MAX_SIZE（100），不支持动态扩容。
 */

#define MAX_SIZE 100

/*
 * Charstack —— 字符栈结构体
 *
 * data - 存储字符的数组
 * top  - 栈顶指针，-1 表示空栈
 */
typedef struct
{
    char data[MAX_SIZE];
    int top;
} Charstack;

/* 初始化栈（top = -1） */
void charstack_init(Charstack *charstack);

/* 判断栈是否为空 */
bool charstack_is_empty(const Charstack *charstack);

/* 判断栈是否已满 */
bool charstack_is_full(const Charstack *charstack);

/* 压栈：把字符放到栈顶 */
bool charstack_push(Charstack *charstack, char op);

/* 弹栈：取出栈顶字符并移除 */
bool charstack_pop(Charstack *charstack, char *out);

/* 看栈顶：读取栈顶字符但不移除 */
bool charstack_peek(const Charstack *charstack, char *out);

#endif