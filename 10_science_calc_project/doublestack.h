#ifndef Doublestack_H
#define Doublestack_H
#include <stdbool.h>

/*
 * ============================================================
 *  doublestack.h —— 双精度浮点数栈
 * ============================================================
 *  用途：
 *      在 eval_postfix 中存放操作数和中间计算结果。
 *      数字压栈，运算符弹两个操作数计算后把结果压回栈。
 *
 *  容量：固定 MAX_SIZE（100），不支持动态扩容。
 */

#define MAX_SIZE 100

/*
 * Doublestack —— 双精度浮点数栈结构体
 *
 * data - 存储 double 的数组
 * top  - 栈顶指针，-1 表示空栈
 */
typedef struct
{
    double data[MAX_SIZE];
    int top;
} Doublestack;

/* 初始化栈（top = -1） */
void doublestack_init(Doublestack *doublestack);

/* 判断栈是否为空 */
bool doublestack_is_empty(const Doublestack *doublestack);

/* 判断栈是否已满 */
bool doublestack_is_full(const Doublestack *doublestack);

/* 压栈：把 double 值放到栈顶 */
bool doublestack_push(Doublestack *doublestack, double value);

/* 弹栈：取出栈顶值并移除 */
bool doublestack_pop(Doublestack *doublestack, double *output);

/* 看栈顶：读取栈顶值但不移除 */
bool doublestack_peek(const Doublestack *doublestack, double *output);

#endif