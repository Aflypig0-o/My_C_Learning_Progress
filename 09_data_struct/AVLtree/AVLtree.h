#ifndef AVLTREE_H
#define AVLTREE_H

typedef struct AVLNode
{
    int data;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
    int (*get_height)(struct AVLNode *self);
    void (*update_height)(struct AVLNode *self);
    int (*get_balance) (struct AVLNode *self);
    void (*dump) (struct AVLNode *self);
    void (*destroy) (struct AVLNode *self);
}AVLNode;

AVLNode *new_node(int val);
AVLNode *insert(AVLNode *root,int val);
AVLNode *build_demo();
AVLNode *avl_delete(AVLNode *root,int val);

#endif