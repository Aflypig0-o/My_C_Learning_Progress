#include <stdio.h>
#include <stdlib.h>
#include "AVLtree.h"

static AVLNode *rotate_left(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *B = x->right;
    x->right = y;
    y->left = B;
    y->update_height(y);
    x->update_height(x);
    return x;
}

static AVLNode *rotate_right(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *B = y->left;
    y->left = x;
    x->right = B;
    x->update_height(x);
    y->update_height(y);
    return y;
}

static AVLNode *rebalance(AVLNode *root)
{
    if(root == NULL) return NULL;
    root->update_height(root);
    int bf = root->get_balance(root);
    fprintf(stderr, "[reb] node=%d h=%d bf=%d L=%p R=%p\n",
            root->data, root->height, bf,
            (void*)root->left, (void*)root->right);
    return root;
}

static int get_height_impl(AVLNode *self){ return self==NULL?-1:self->height; }
static void update_height_impl(AVLNode *self){
    if(self==NULL)return;
    int lh=self->get_height(self->left), rh=self->get_height(self->right);
    self->height=(lh>rh?lh:rh)+1;
}
static int get_balance_impl(AVLNode *self){
    return self->get_height(self->left)-self->get_height(self->right);
}
static void dump_impl(AVLNode *self){
    if(!self)return;
    self->dump(self->left);
    printf("%d(h%d,bf%d) ",self->data,self->height,self->get_balance(self));
    self->dump(self->right);
}
static void destroy_impl(AVLNode *self){
    if(!self)return;
    self->destroy(self->left); self->destroy(self->right); free(self);
}

AVLNode *new_node(int val)
{
    AVLNode *p=(AVLNode*)malloc(sizeof(AVLNode));
    if(!p){perror("malloc");return NULL;}
    p->data=val; p->height=0; p->left=NULL; p->right=NULL;
    p->get_height=get_height_impl; p->update_height=update_height_impl;
    p->get_balance=get_balance_impl; p->dump=dump_impl; p->destroy=destroy_impl;
    return p;
}

AVLNode *insert(AVLNode *root,int val)
{
    if(root==NULL) return new_node(val);
    if(val<root->data) root->left=insert(root->left,val);
    else if(val>root->data) root->right=insert(root->right,val);
    else return root;
    return rebalance(root);
}
