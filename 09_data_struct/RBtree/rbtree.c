#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

/* ============================================================
 * 约定：用 NULL 表示空叶子，且把 NULL 视为黑色。
 * （教材里的黑色 TNULL 哨兵只是为了少判空，本质相同。）
 * ============================================================ */

static int is_red(RBNode *n)
{
    return n != NULL && n->color == RED;
}

static int is_black(RBNode *n)
{
    return n == NULL || n->color == BLACK;
}

RBNode *rb_new(int val, int color)
{
    RBNode *p = (RBNode *)malloc(sizeof(RBNode));
    if (p == NULL) { perror("malloc"); exit(EXIT_FAILURE); }
    p->data   = val;
    p->color  = color;
    p->left   = NULL;
    p->right  = NULL;
    p->parent = NULL;
    return p;
}

/* ============================================================
 * 旋转（带 parent 的版本）
 * 核心两行和 AVL 完全一样：x->right = y; y->left = B;
 * 多出来的是：B->parent、y->parent、爷爷的孩子指针、根的更新。
 * ============================================================ */

static void rotate_left(RBNode **root, RBNode *x)
{
    RBNode *y = x->right;
    RBNode *B = y->left;

    x->right = B;
    if (B != NULL) B->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

static void rotate_right(RBNode **root, RBNode *y)
{
    RBNode *x = y->left;
    RBNode *B = x->right;

    y->left = B;
    if (B != NULL) B->parent = y;

    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

/* ============================================================
 * 插入修复
 * 矛盾：z 和 z->parent 都是红色。看叔叔：
 *   叔叔红 → 父叔变黑，爷爷变红，z 上移到爷爷继续
 *   叔叔黑 → 一字型：父变黑、爷爷变红、对爷爷旋转，结束
 *            拐弯型：先对父旋转成一字型，再按上面处理
 * ============================================================ */

static void insert_fixup(RBNode **root, RBNode *z)
{
    while (z->parent != NULL && is_red(z->parent))
    {
        RBNode *p = z->parent;
        RBNode *g = p->parent;

        if (p == g->left)
        {
            RBNode *u = g->right;                 /* 叔叔 */

            if (is_red(u))
            {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            }
            else
            {
                if (z == p->right)                /* 拐弯：先拉直 */
                {
                    rotate_left(root, p);
                    z = p;
                    p = z->parent;
                    g = p->parent;
                }
                p->color = BLACK;                 /* 一字型 */
                g->color = RED;
                rotate_right(root, g);
            }
        }
        else
        {
            RBNode *u = g->left;

            if (is_red(u))
            {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            }
            else
            {
                if (z == p->left)
                {
                    rotate_right(root, p);
                    z = p;
                    p = z->parent;
                    g = p->parent;
                }
                p->color = BLACK;
                g->color = RED;
                rotate_left(root, g);
            }
        }
    }
    (*root)->color = BLACK;
}

RBNode *rb_insert(RBNode *root, int val)
{
    RBNode *z = rb_new(val, RED);          /* 新节点永远红色 */

    if (root == NULL)
    {
        z->color = BLACK;
        return z;
    }

    /* ① 标准 BST 插入 */
    RBNode *cur = root, *parent = NULL;
    while (cur != NULL)
    {
        parent = cur;
        if (val < cur->data)      cur = cur->left;
        else if (val > cur->data) cur = cur->right;
        else { free(z); return root; }     /* 重复值 */
    }
    z->parent = parent;
    if (val < parent->data) parent->left  = z;
    else                    parent->right = z;

    /* ② 修复 */
    insert_fixup(&root, z);
    return root;
}

/* ============================================================
 * 删除
 * ============================================================ */

/* 用子树 v 顶替子树 u 的位置（v 可以是 NULL） */
static void transplant(RBNode **root, RBNode *u, RBNode *v)
{
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

static RBNode *min_node(RBNode *n)
{
    while (n->left != NULL) n = n->left;
    return n;
}

/* ------------------------------------------------------------
 * 删除修复
 *
 * x 是"顶替上来的节点"，可能为 NULL。
 * 因为 x 可能是 NULL（读不到 x->parent），所以额外传一个 x_parent。
 *
 * 记账方式：x 这一支比别的路径少了一层黑，需要把这个缺口补掉。
 * 设 s 是兄弟（x 在左边时 s = parent->right）：
 *
 *   情况 1：s 红
 *        s 变黑、parent 变红、对 parent 左旋 → 转成 2/3/4
 *   情况 2：s 黑，s 两个孩子都黑
 *        s 变红，缺口上推给 parent，x 上移
 *   情况 3：s 黑，s 左孩子红、右孩子黑
 *        s 左孩子变黑、s 变红、对 s 右旋 → 转成情况 4
 *   情况 4：s 黑，s 右孩子红
 *        s 继承 parent 的颜色，parent 变黑，s 右孩子变黑，
 *        对 parent 左旋，结束
 *
 * 对称情况把 left/right 互换即可。
 * ------------------------------------------------------------ */
static void delete_fixup(RBNode **root, RBNode *x, RBNode *x_parent)
{
    /* 只有"x 是黑的"才需要补黑 */
    while (x != *root && is_black(x))
    {
        if (x_parent == NULL) break;      /* 理论上不会发生 */

        if (x == x_parent->left)
        {
            RBNode *s = x_parent->right;  /* 兄弟 */

            if (s == NULL)                /* 防御：兄弟不可能为空，但保险 */
            {
                x = x_parent;
                x_parent = x->parent;
                continue;
            }

            if (is_red(s))                       /* 情况 1 */
            {
                s->color = BLACK;
                x_parent->color = RED;
                rotate_left(root, x_parent);
                s = x_parent->right;
            }

            if (is_black(s->left) && is_black(s->right))   /* 情况 2 */
            {
                s->color = RED;
                x = x_parent;
                x_parent = x->parent;
            }
            else
            {
                if (is_black(s->right))                    /* 情况 3 */
                {
                    s->left->color = BLACK;
                    s->color = RED;
                    rotate_right(root, s);
                    s = x_parent->right;
                }
                /* 情况 4 */
                s->color = x_parent->color;
                x_parent->color = BLACK;
                s->right->color = BLACK;
                rotate_left(root, x_parent);
                x = *root;
                x_parent = NULL;
            }
        }
        else
        {
            /* 镜像：x 是右孩子 */
            RBNode *s = x_parent->left;

            if (s == NULL)
            {
                x = x_parent;
                x_parent = x->parent;
                continue;
            }

            if (is_red(s))
            {
                s->color = BLACK;
                x_parent->color = RED;
                rotate_right(root, x_parent);
                s = x_parent->left;
            }

            if (is_black(s->left) && is_black(s->right))
            {
                s->color = RED;
                x = x_parent;
                x_parent = x->parent;
            }
            else
            {
                if (is_black(s->left))
                {
                    s->right->color = BLACK;
                    s->color = RED;
                    rotate_left(root, s);
                    s = x_parent->left;
                }
                s->color = x_parent->color;
                x_parent->color = BLACK;
                s->left->color = BLACK;
                rotate_right(root, x_parent);
                x = *root;
                x_parent = NULL;
            }
        }
    }

    if (x != NULL)
        x->color = BLACK;   /* 根、或补完黑的节点，染黑收尾 */
}

RBNode *rb_delete(RBNode *root, int val)
{
    /* ① 先找 */
    RBNode *z = root;
    while (z != NULL && z->data != val)
        z = (val < z->data) ? z->left : z->right;
    if (z == NULL) return root;            /* 没找到 */

    RBNode *x;            /* 顶替上来的节点 */
    RBNode *x_parent;     /* x 的父亲（x 为 NULL 时也要知道） */
    RBColor y_orig;       /* 真正"移走"的那个节点的原色 */

    if (z->left == NULL)
    {
        x = z->right;
        x_parent = z->parent;
        y_orig = z->color;
        transplant(&root, z, z->right);
    }
    else if (z->right == NULL)
    {
        x = z->left;
        x_parent = z->parent;
        y_orig = z->color;
        transplant(&root, z, z->left);
    }
    else
    {
        /* 两个孩子：用右子树最小值 y 顶替 z */
        RBNode *y = min_node(z->right);
        y_orig = y->color;
        x = y->right;

        if (y->parent == z)
        {
            x_parent = y;                  /* x 直接挂在 y 下面 */
            if (x != NULL) x->parent = y;  /* 已有，保险起见 */
        }
        else
        {
            x_parent = y->parent;          /* 记下 y 原来的父亲 */
            transplant(&root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(&root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;               /* 继承 z 的颜色 */
    }

    /* ② 如果移走的是黑节点，缺口需要补 */
    if (y_orig == BLACK)
        delete_fixup(&root, x, x_parent);

    free(z);
    return root;
}

/* ============================================================
 * 查找 / 遍历 / 释放
 * ============================================================ */

RBNode *rb_find(RBNode *root, int val)
{
    while (root != NULL && root->data != val)
        root = (val < root->data) ? root->left : root->right;
    return root;
}

void rb_dump_inorder(RBNode *n)
{
    if (n == NULL) return;
    rb_dump_inorder(n->left);
    printf("%d(%s) ", n->data, n->color == RED ? "R" : "B");
    rb_dump_inorder(n->right);
}

void rb_destroy(RBNode *n)
{
    if (n == NULL) return;
    rb_destroy(n->left);
    rb_destroy(n->right);
    free(n);
}

/* ============================================================
 * 校验
 * ============================================================ */

static int check_inorder(RBNode *n, int *prev, int *first)
{
    if (n == NULL) return 1;
    if (!check_inorder(n->left, prev, first)) return 0;
    if (!*first && n->data <= *prev) return 0;
    *first = 0;
    *prev = n->data;
    if (!check_inorder(n->right, prev, first)) return 0;
    return 1;
}

int rb_is_bst(RBNode *root)
{
    int prev = 0, first = 1;
    return check_inorder(root, &prev, &first);
}

static int count_black(RBNode *n)
{
    if (n == NULL) return 1;               /* NULL 算一层黑 */
    int l = count_black(n->left);
    int r = count_black(n->right);
    if (l != r || l < 0 || r < 0) return -1;
    return l + (n->color == BLACK ? 1 : 0);
}

int rb_black_height(RBNode *root)
{
    return count_black(root);
}

/* 递归检查：红红相邻、父子指针一致，返回 1 通过 */
static int check_tree(RBNode *n, RBNode *parent)
{
    if (n == NULL) return 1;
    if (n->parent != parent) return 0;
    if (is_red(n) && (is_red(n->left) || is_red(n->right))) return 0;
    return check_tree(n->left, n) && check_tree(n->right, n);
}

int rb_check(RBNode *root)
{
    if (!rb_is_bst(root))            return 0;   /* 性质：BST */
    if (root != NULL && is_red(root)) return 0; /* 性质 2：根黑 */
    if (!check_tree(root, NULL))      return 0; /* 性质 4 + parent */
    if (rb_black_height(root) < 0)    return 0; /* 性质 5 */
    return 1;
}
