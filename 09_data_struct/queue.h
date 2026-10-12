#ifndef QUENE_H
#define QUENE_H
#include <stdbool.h>
#include <stdio.h>

typedef struct QNode
{
    int data;
    struct QNode *next;
}QNode;

typedef struct
{
    
    QNode *front;
    QNode *rear;
    size_t size;
}Queue;

void quene_init(Queue *q);
bool queue_is_empty(const Queue *q);
size_t queue_size(const Queue *q);
bool queue_enqueue(Queue *q,int value);
bool queue_dequeue(Queue *q,int *out);
bool queue_peek(const Queue *q,int *out);
void queue_destory(Queue *q);
void queue_print(const Queue *q);

#endif