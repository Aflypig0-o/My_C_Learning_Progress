#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

static int is_black(RBNode *root){
    return root != NULL && root->color == BLACK;
}

static int is_red(RBNode *root){
    return root != NULL && root->color == RED;
}

static void rotate_left(RBNode **root,RBNode *x){
    RBNode *y = x->right;
    RBNode *B = y->left;
    x->right = B;
    if(B != NULL){
        B->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL){
        *root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
static void rotate_right(RBNode **root,RBNode *y){
    RBNode *x = y->left;
    RBNode *B = x->right;
    y->left = B;
    if(B != NULL){
        B->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == NULL){
        *root = x;
    }
    else if (y == y->parent->left){
        y->parent->left = x;
    }
    else{
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}