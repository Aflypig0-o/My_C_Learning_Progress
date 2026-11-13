#ifndef RBTREE_H
#define RBTREE_H
#include <stdbool.h>

typedef enum {RED,BLACK} RBColor;

typedef struct RBNode
{
    int data;
    RBColor color;
    struct RBNode *parent;
    struct RBNode *left;
    struct RBNode *right;
    void (*rb_destroy) (struct RBNode *root);
    void (*dump_inorder) (struct RBNode *root);
}RBNode;

RBNode *insert(RBNode *root,int val);
RBNode *rb_create(int val,int color);
bool rb_check(RBNode *root);
#endif