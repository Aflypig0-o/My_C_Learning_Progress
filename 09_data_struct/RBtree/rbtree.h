#ifndef RBTREE_H
#define RBTREE_H

typedef enum {RED,BLACK} RBColor;

typedef struct RBNode
{
    int data;
    RBColor color;
    struct RBNode *parent;
    struct RBNode *left;
    struct RBNode *right;
}RBNode;

#endif