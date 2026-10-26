#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include <stdbool.h>

typedef struct QNode QNode;
typedef struct Queue Queue;

struct QNode
{
    int data;
    struct Queue *next;
};

struct  Queue
{
    QNode *head;
    QNode *tail;
    size_t size;
    void (*enqueue)(Queue *self, int val); // 入队
    bool (*dequeue)(Queue *self, int *out_val); // 出队
    bool (*is_empty)(Queue *self); // 判空
    void (*destroy)(Queue *self);  // 销毁
};

Queue *create_queue();

#endif