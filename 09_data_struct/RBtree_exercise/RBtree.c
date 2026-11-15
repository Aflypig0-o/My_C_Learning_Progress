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

static void rb_destroy_impl(RBNode *root){
    if(root == NULL) return;
    rb_destroy_impl(root->left);
    rb_destroy_impl(root->right);
    free(root);
}

static void dump_inorder_impl(RBNode *root){
    if(root == NULL) return;
    dump_inorder_impl(root->left);
    printf("%d ",root->data);
    dump_inorder_impl(root->right);
}

static void insert_fixup(RBNode **root,RBNode *z){
    while(z->parent != NULL && is_red(z->parent)){
        RBNode *p = z->parent;
        RBNode *g = p->parent;
        if(p == g->left){
            RBNode *u = g->right;
            if(is_red(u)){
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            }
            else{
                if(z == p->right){
                    rotate_left(root,p);
                    z = p;
                    p = z->parent;
                    g = p->parent;
                }
                g->color = RED;
                p->color = BLACK;
                rotate_right(root,g);
            }
        }
        else{
            RBNode *u = g->left;
            if(is_red(u)){
                u->color = BLACK;
                p->color = BLACK;
                g->color = RED;
                z = g;
            }
            else{
                if(z == p->left){
                    rotate_right(root,p);
                    z = p;
                    p = z->parent;
                    g = p->parent;
                }
                g->color = RED;
                p->color = BLACK;
                rotate_left(root,g);
            }
        }
    }
    (*root)->color = BLACK;
}

RBNode *insert(RBNode *root,int val){
    RBNode *new_node = rb_create(val,RED);
    if(root == NULL){
        new_node->color = BLACK;
    }
    RBNode *curr = root,*parent = NULL;
    while(curr != NULL){
        parent = curr;
        if(val < curr->data) curr = curr->left;
        else if (val > curr->data) curr = curr->right;
        else{
            free(new_node);
            return root;
        }
    }
    new_node->parent = parent;
    if(val < parent->data){
        parent->left = new_node;
    }
    else{
        parent->right = new_node;
    }
    insert_fixup(&root,new_node);
    return root;
}

RBNode *rb_create(int val,RBColor color){
    RBNode *rb = (RBNode*)malloc(sizeof(RBNode));
    if(rb == NULL){
        perror("malloc");
        return NULL;
    }
    rb->data = val;
    rb->color = color;
    rb->left = rb->right = rb->parent = NULL;
    rb->rb_destroy = rb_destroy_impl;
    rb->dump_inorder = dump_inorder_impl;
    return rb;
}