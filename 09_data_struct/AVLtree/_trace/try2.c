#include <stdio.h>
#include <stdlib.h>
#include "AVLtree.h"

static AVLNode *rotate_right(AVLNode *y)
{
    AVLNode *x = y->left; /*升上来的那个*/
    AVLNode *B = x->right; /*y的内孙*/
    x->right = y; /*让y成为x的右儿子*/
    y->left = B; /*让y的内孙成为y的左儿子*/
    y->update_height(y);/*更新y的高度*/
    x->update_height(x);/*更新x的高度，此处必须先更新y，因为x的高度由y算出*/
    return x;
}

static AVLNode *rotate_left(AVLNode *x)
{    AVLNode *y = x->right;
    AVLNode *B = y->left;
    y->left = x;
    x->right = B;
    x->update_height(x);
    y->update_height(y);
    return y;
}

static AVLNode *rebalance(AVLNode *root)
{
    if(root == NULL)
    {
        return NULL;
    }
    root->update_height(root);
    int bf = root->get_balance(root);

    if(bf > 1)
    {
        if(root->left->get_balance(root->left) >= 0)
        {
            return rotate_right(root);//LL，右旋
        }
        root->left = rotate_left(root->left);//LR，左旋，右旋
        return rotate_right(root);
    }
    if(bf < -1)
    {
        if(root->right->get_balance(root->right) <=0)
        {
            return rotate_left(root);//RR，左旋
        }
        root->right = rotate_right(root->right);//RL，先对右子右旋
        return rotate_left(root);
    }
    return root;
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

    return rebalance(root);
}