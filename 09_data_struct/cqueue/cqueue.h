#ifndef CQUEUE_H
#define CQUEUE_H

#include <stdbool.h>
#include <stdlib.h>

// 前置声明
typedef struct CQueue CQueue;

// 循环队列“类”
struct CQueue {
    int *data;      // 动态数组
    int capacity;   // 数组总容量（实际能存 capacity - 1 个）
    int front;      // 队首下标
    int rear;       // 队尾下标（指向下一个空位置）

    // 面向对象的技能槽（函数指针）
    bool (*enqueue)(CQueue *self, int val);
    bool (*dequeue)(CQueue *self,int *out_val);
    int (*get_front)(CQueue *self);
    int (*get_rear)(CQueue *self);
    bool (*is_empty)(CQueue *self);
    bool (*is_full)(CQueue *self);
    void (*destroy)(CQueue *self);
};

// 暴露给外界的构造函数
CQueue* cqueue_create(int k);

#endif