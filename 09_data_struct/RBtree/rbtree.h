#ifndef RBTREE_H
#define RBTREE_H

typedef enum { RED, BLACK } RBColor;

typedef struct RBNode
{
    int data;
    RBColor color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;   /* 红黑树修复需要往上走，所以必须存父亲 */
} RBNode;

/* ---------- 基本操作 ---------- */
RBNode *rb_new(int val, int color);
RBNode *rb_insert(RBNode *root, int val);
RBNode *rb_delete(RBNode *root, int val);
RBNode *rb_find(RBNode *root, int val);

/* ---------- 遍历与释放 ---------- */
void rb_dump_inorder(RBNode *n);
void rb_destroy(RBNode *n);

/* ---------- 校验（学习/测试用） ---------- */
int rb_is_bst(RBNode *root);        /* 中序是否严格升序 */
int rb_black_height(RBNode *root);  /* 黑高；-1 表示不等 */
int rb_check(RBNode *root);         /* 五条性质全查，返回 1 通过 */

#endif
