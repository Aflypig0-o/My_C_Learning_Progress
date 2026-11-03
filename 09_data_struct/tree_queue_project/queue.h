#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>
#include "tree.h"

typedef struct Queue Queue;

struct Queue
{
    TreeNode **data;
    int front;
    int rear;
    int capacity;
    bool (*is_empty)(Queue *self);
    void (*enqueue)(Queue *self,TreeNode *node);
    TreeNode* (*dequeue)(Queue *self);
    void (*destroy)(Queue *self);
};

Queue *queue_create(int capacity);

#endif