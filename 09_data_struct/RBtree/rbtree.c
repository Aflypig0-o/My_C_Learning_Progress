#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "RBtree.h"

static bool is_red(RBNode *root){
    return root != NULL && root->color == RED;
}

static bool is_black(RBNode *root){
    return root == NULL || root->color == BLACK;
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

static void insert_fixup(RBNode **root,RBNode *z){
    while(z->parent != NULL && is_red(z->parent)){
        RBNode *p = z->parent;//z的父节点
        RBNode *g = p->parent;//z的祖父节点
        if(p == g->left){//如果p是g的左节点
            RBNode *u = g->right;//那么，叔叔节点u就是g的右儿子
            if(is_red(u)){//如果u也为红色，
                p->color = BLACK;//p变为黑色
                u->color = BLACK;//u变为黑色
                g->color = RED;//g变为红色
                z = g;
            }
            else{//u为黑色，进行旋转
                if(z == p->right){//LR型，拉直后右旋
                    rotate_left(root,p);
                    z = p;
                    p = z->parent;
                    g = p->parent;
                }
                g->color = RED;
                p->color = BLACK;
                rotate_right(root,g);//右旋
            }
        }
        else{
            RBNode *u = g->left;//否则，叔叔节点u就是g的左儿子
            if(is_red(u)){//如果u也为红色
                p->color = BLACK;//p变为黑色
                u->color = BLACK;//u变为黑色
                g->color = RED;//g变为黑色
                z = g;
            }
            else{//u为黑色
                if(z == p->left){//RL型，拉直
                    rotate_right(root,p);
                    z = p;
                    p = z->parent;
                    g = p->parent;
                }
                g->color = RED;
                p->color = BLACK;
                rotate_left(root,g);//左旋
            }
        }
    }
    (*root)->color = BLACK;//根必须黑
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

static bool check_inorder(RBNode *root,int *prev,bool *first){
    if(root == NULL)return true;
    if(!check_inorder(root->left,prev,first)) return false;
    if(!*first && root->data <= *prev) return false;
    *first = false;
    *prev = root->data;
    return check_inorder(root->right,prev,first);
}

static bool check_red(RBNode *root){
    if(root == NULL) return true;
    if(is_red(root)){
        if(is_red(root->left) || is_red(root->right)){
            return false;
        }
    }
    return check_red(root->left) && check_red(root->right);
}

static int count_black(RBNode *root){
    if(root == NULL) return 1;
    int l = count_black(root->left);
    int r = count_black(root->right);
    if(l < 0 || r < 0) return -1;
    if(l != r) return -1;
    return l + (root->color == BLACK ? 1:0);
}

static void transplant(RBNode **root,RBNode *u,RBNode *v){

}

RBNode *insert(RBNode *root,int val){
    RBNode *new_node = rb_create(val,RED);//新建一个new_node节点
    if(root == NULL){
        new_node->color = BLACK;//此处插入的是根节点，染黑
        return new_node;
    }
    RBNode *curr  = root,*parent = NULL;
    while(curr != NULL){
        parent = curr;//记录curr移动前位置
        if(val < curr->data){
        curr = curr->left;
        }
        else if(val > curr->data){
        curr = curr->right;
        }
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

RBNode *rb_create(int val,int color){
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

bool rb_check(RBNode *root){
    int prev = 0;
    bool first = true;
    if(!check_inorder(root, &prev, &first)) return false;
    if(root != NULL && root->color != BLACK) return false;
    if(!check_red(root)) return false;
    if(count_black(root) < 0) return false;
    return true;
}

