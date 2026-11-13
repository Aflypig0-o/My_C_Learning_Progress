#ifndef RBNode_H
#define RBNode_H

typedef enum {RED,BLACK} RBColor;

typedef struct RBNode{
    int data;
    RBColor color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
    void (*destroy) (struct RBNode *root);
    void (*dump_inorder) (struct RBNode *root);
}RBNode;

RBNode *rb_create(int val,RBColor color);
RBNode *insert(RBNode *root,int val);

#endif