#include <stdio.h>
#include <stdlib.h>
#include "RBtree.h"

static int cnt(RBNode *n){ return n ? 1 + cnt(n->left) + cnt(n->right) : 0; }

static int inorder_ok(RBNode *n, int *prev, bool *first)
{
    if (!n) return 1;
    if (!inorder_ok(n->left, prev, first)) return 0;
    if (!*first && n->data <= *prev) return 0;
    *first = false;
    *prev = n->data;
    return inorder_ok(n->right, prev, first);
}

static int parent_ok(RBNode *n, RBNode *p)
{
    if (!n) return 1;
    if (n->parent != p) return 0;
    return parent_ok(n->left, n) && parent_ok(n->right, n);
}

static int struct_ok(RBNode *r)
{
    int prev = 0; bool first = true;
    return inorder_ok(r, &prev, &first) && parent_ok(r, NULL);
}

static void print_tree(RBNode *n, int d)
{
    if (!n) return;
    print_tree(n->right, d+1);
    for (int i = 0; i < d; i++) printf("    ");
    printf("%d(%c)\n", n->data, n->color == RED ? 'R' : 'B');
    print_tree(n->left, d+1);
}

int main(void)
{
    int fails = 0;

    /* 1. 删双孩子：情况 A（succ 就是右孩子） */
    printf("=== 1. 双孩子简化形态 ===\n");
    {
        RBNode *r = NULL;
        int v[] = {20, 10, 30};
        for (int i = 0; i < 3; i++) r = insert(r, v[i]);
        printf("初始:\n"); print_tree(r, 1);
        r = rb_delete(r, 20);          /* 20 有两孩子 10、30 */
        printf("删 20 后:\n"); print_tree(r, 1);
        printf("中序: "); r->dump_inorder(r);
        printf("\n结构=%s 节点=%d\n\n", struct_ok(r)?"OK":"FAIL", cnt(r));
        if (!struct_ok(r) || cnt(r) != 2) fails++;
        r->rb_destroy(r);
    }

    /* 2. 删双孩子：情况 B（succ 在深处） */
    printf("=== 2. succ 在深处 ===\n");
    {
        RBNode *r = NULL;
        int v[] = {20, 10, 40, 30, 50, 25, 35};
        for (int i = 0; i < 7; i++) r = insert(r, v[i]);
        printf("初始:\n"); print_tree(r, 1);
        printf("中序: "); r->dump_inorder(r); printf("\n");

        r = rb_delete(r, 20);          /* 后继 25 在深处 */
        printf("删 20 后:\n"); print_tree(r, 1);
        printf("中序: "); r->dump_inorder(r);
        printf("\n结构=%s 节点=%d\n\n", struct_ok(r)?"OK":"FAIL", cnt(r));
        if (!struct_ok(r) || cnt(r) != 6) fails++;
        r->rb_destroy(r);
    }

    /* 3. 删根，且根有两个孩子 */
    printf("=== 3. 删根 ===\n");
    {
        RBNode *r = NULL;
        int v[] = {50, 30, 70, 20, 40, 60, 80};
        for (int i = 0; i < 7; i++) r = insert(r, v[i]);
        r = rb_delete(r, 50);
        printf("删 50 后中序: "); r->dump_inorder(r);
        printf("\n结构=%s 节点=%d\n\n", struct_ok(r)?"OK":"FAIL", cnt(r));
        if (!struct_ok(r) || cnt(r) != 6) fails++;
        r->rb_destroy(r);
    }

    /* 4. 全部删光（顺序） */
    printf("=== 4. 顺序删光 ===\n");
    {
        RBNode *r = NULL;
        int v[100];
        for (int i = 0; i < 100; i++) { v[i] = i*2; r = insert(r, v[i]); }
        int ok = 1;
        for (int i = 0; i < 100; i++) {
            int before = cnt(r);
            r = rb_delete(r, v[i]);
            if (cnt(r) != before-1 || !struct_ok(r)) { ok = 0; printf("  删 %d 失败\n", v[i]); break; }
        }
        printf("结果=%s 最终节点=%d\n\n", ok?"OK":"FAIL", cnt(r));
        if (!ok) fails++;
    }

    /* 5. 全部删光（逆序） */
    printf("=== 5. 逆序删光 ===\n");
    {
        RBNode *r = NULL;
        int v[100];
        for (int i = 0; i < 100; i++) { v[i] = i*2; r = insert(r, v[i]); }
        int ok = 1;
        for (int i = 99; i >= 0; i--) {
            int before = cnt(r);
            r = rb_delete(r, v[i]);
            if (cnt(r) != before-1 || !struct_ok(r)) { ok = 0; printf("  删 %d 失败\n", v[i]); break; }
        }
        printf("结果=%s 最终节点=%d\n\n", ok?"OK":"FAIL", cnt(r));
        if (!ok) fails++;
    }

    /* 6. 随机增删（结构正确性） */
    printf("=== 6. 随机增删 3000 次 ===\n");
    {
        srand(20261115);
        RBNode *r = NULL;
        int live[300], nlive = 0;
        int ok = 1;
        for (int step = 0; step < 3000 && ok; step++) {
            int v = rand() % 300;
            int idx = -1;
            for (int k = 0; k < nlive; k++) if (live[k] == v) { idx = k; break; }

            if (idx >= 0) {
                int before = cnt(r);
                r = rb_delete(r, v);
                live[idx] = live[--nlive];
                if (cnt(r) != before-1 || !struct_ok(r)) ok = 0;
            } else {
                int before = cnt(r);
                r = insert(r, v);
                live[nlive++] = v;
                if (cnt(r) != before+1 || !struct_ok(r)) ok = 0;
            }
        }
        printf("结果=%s 剩余节点=%d\n", ok?"OK":"FAIL", cnt(r));
        if (!ok) fails++;
        if (r) r->rb_destroy(r);
    }

    printf("\n=== %s ===\n", fails ? "有失败" : "阶段二全部通过（结构层面）");
    return fails ? 1 : 0;
}
