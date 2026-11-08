#include <stdio.h>
#include <stdlib.h>
#include "AVLtree.h"

static AVLNode *rotate_left(AVLNode *y)
{

}

static AVLNode *rotate_right(AVLNode *x)
{

}

static AVLNode *balance(AVLNode *root)
{
    ;
}

static int get_height_impl(AVLNode *self)
{
    return self == NULL ? -1 : self->height;
}

static void update_height_impl(AVLNode *self)
{
    if(self == NULL)
    {
        return;
    }
    int left_height = self->get_height(self->left);
    int right_height = self->get_height(self->right);
    self->height = (left_height > right_height ? left_height : right_height) + 1;
}

static int get_balance_impl(AVLNode *self)
{
    return self->get_height(self->left) - self->get_height(self->right);
}

static void dump_impl(AVLNode *self)
{
    if(self == NULL)
    {
        return;
    }
    self->dump(self->left);
    printf("节点 %d: height=%d  BF=%d\n", self->data, self->height, self->get_balance(self));
    self->dump(self->right);
}

static void destroy_impl(AVLNode *self)
{
    if(self == NULL)
    {
        return;
    }
    self->destroy(self->left);
    self->destroy(self->right);
    free(self);
}

AVLNode *new_node(int val)
{
    AVLNode *p = (AVLNode*)malloc(sizeof(AVLNode));
    if(p == NULL)
    {
        perror("malloc");
        return NULL;
    }
    p->data = val;
    p->height = 0;
    p->left = NULL;
    p->right = NULL;
    p->get_height = get_height_impl;
    p->update_height = update_height_impl;
    p->get_balance = get_balance_impl;
    p->dump = dump_impl;
    p->destroy = destroy_impl;
    return p;
}

AVLNode *build_demo()
{
    AVLNode *F = new_node(6);
    AVLNode *D = new_node(4);
    AVLNode *E = new_node(5);
    E->left = F;
    E->update_height(E);

    AVLNode *B = new_node(2);
    B->left = D;
    B->right = E;
    B->update_height(B);

    AVLNode *C = new_node(3);
    AVLNode *A = new_node(1);
    A->left = B;
    A->right = C;
    A->update_height(A);

    return A;
}

AVLNode *insert(AVLNode *root,int val)
{
    if(root == NULL)
    {
        return new_node(val);
    }

    if(val < root->data)
    {
        root->left = insert(root->left,val);
    }
    else if(val > root->data)
    {
        root->right = insert(root->right,val);
    }
    else
    {
        return root;
    }

    root->update_height(root);
    return balance(root);
}