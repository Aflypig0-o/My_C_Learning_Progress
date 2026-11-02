#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>
#include "tree.h"
#define MAX_Q_SIZE 100

typedef struct
{
    TreeNode* data[MAX_Q_SIZE]; 
    int front;
    int rear;
}Queue;

void init_queue(Queue *q);
bool is_empty(Queue *q);
void enqueue(Queue *q,TreeNode *node);
TreeNode *dequeue(Queue *q);

#endif