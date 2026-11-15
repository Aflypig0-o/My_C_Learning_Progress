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

static RBNode *my_find(RBNode *n, int v)
{
    while (n && n->data != v)
        n = (v < n->data) ? n->left : n->right;
    return n;
}

static int parent_ok(RBNode *n, RBNode *p)
{
    if (!n) return 1;
    if (n->parent != p) return 0;
    return parent_ok(n->left, n) && parent_ok(n->right, n);
}

int main(void)
{
    int fails = 0;

    /* 阶段一：只测结构，不测颜色 */
    printf("=== 阶段一：删叶子节点 ===\n");
    {
        RBNode *r = NULL;
        r = insert(r, 10); r = insert(r, 5); r = insert(r, 15);
        printf("初始: "); (r ? r->dump_inorder(r), (void)0 : (void)printf("(空树)")); printf(" (节点=%d)\n", cnt(r));

        r = rb_delete(r, 5);
        printf("删 5: "); (r ? r->dump_inorder(r), (void)0 : (void)printf("(空树)")); printf(" (节点=%d)\n", cnt(r));
        if (cnt(r) != 2) { printf("  !! 节点数错\n"); fails++; }

        r = rb_delete(r, 15);
        printf("删15: "); (r ? r->dump_inorder(r), (void)0 : (void)printf("(空树)")); printf(" (节点=%d)\n", cnt(r));
        if (cnt(r) != 1) { printf("  !! 节点数错\n"); fails++; }

        r = rb_delete(r, 10);
        printf("删10: "); (r ? r->dump_inorder(r), (void)0 : (void)printf("(空树)")); printf(" (节点=%d)\n", cnt(r));
        if (cnt(r) != 0) { printf("  !! 节点数错\n"); fails++; }
        if (r != NULL) { printf("  !! 根应为 NULL\n"); fails++; }
    }

    /* 删只有一个孩子的节点 */
    printf("\n=== 阶段一：删单孩子节点 ===\n");
    {
        RBNode *r = NULL;
        int v[] = {20,10,30,5,15,25,35};
        for (int i = 0; i < 7; i++) r = insert(r, v[i]);
        printf("初始: "); (r ? r->dump_inorder(r), (void)0 : (void)printf("(空树)")); printf("\n");

        r = rb_delete(r, 5);       /* 叶子 */
        printf("删 5: "); (r ? r->dump_inorder(r), (void)0 : (void)printf("(空树)")); printf(" (节点=%d)\n", cnt(r));

        r = rb_delete(r, 10);      /* 10 此时是叶子 */
        printf("删10: "); (r ? r->dump_inorder(r), (void)0 : (void)printf("(空树)")); printf(" (节点=%d)\n", cnt(r));

        r = rb_delete(r, 30);      /* 30 有两个孩子 -> TODO 不处理 */
        printf("删30: "); (r ? r->dump_inorder(r), (void)0 : (void)printf("(空树)")); printf(" (节点=%d) [双孩子，暂不处理]\n", cnt(r));

        int prev = 0; bool first = true;
        int ok = inorder_ok(r, &prev, &first) && parent_ok(r, NULL);
        printf("结构检查: 中序升序+parent一致 = %s\n", ok ? "OK" : "FAIL");
        if (!ok) fails++;
        r->rb_destroy(r);
    }

    /* 删不存在的值 */
    printf("\n=== 阶段一：删不存在的值 ===\n");
    {
        RBNode *r = NULL;
        r = insert(r, 50); r = insert(r, 30); r = insert(r, 70);
        int before = cnt(r);
        r = rb_delete(r, 999);
        int ok = (cnt(r) == before);
        printf("删999: 节点 %d -> %d %s\n", before, cnt(r), ok ? "OK" : "FAIL");
        if (!ok) fails++;
        r->rb_destroy(r);
    }

    /* 随机压力：只删叶子或单孩子节点，验证结构 */
    printf("\n=== 阶段一：随机压测（只删叶子）===\n");
    {
        srand(20261115);
        int bad = 0;
        for (int round = 0; round < 100 && !bad; round++)
        {
            RBNode *r = NULL;
            int live[200], nlive = 0;
            for (int i = 0; i < 100; i++) {
                int v = rand() % 1000;
                int had = 0;
                for (int k = 0; k < nlive; k++) if (live[k] == v) { had = 1; break; }
                if (!had) { r = insert(r, v); live[nlive++] = v; }
            }
            /* 只删叶子节点 */
            int removed = 0;
            for (int k = 0; k < nlive && removed < 30; k++) {
                RBNode *z = my_find(r, live[k]);
                if (z && z->left == NULL && z->right == NULL) {
                    int before = cnt(r);
                    r = rb_delete(r, live[k]);
                    if (cnt(r) != before - 1) { bad++; break; }
                    removed++;
                }
            }
            int prev = 0; bool first = true;
            if (!inorder_ok(r, &prev, &first) || !parent_ok(r, NULL)) bad++;
            r->rb_destroy(r);
        }
        printf("100 轮随机删叶子: %s\n", bad ? "FAIL" : "OK");
        if (bad) fails++;
    }

    printf("\n=== %s ===\n", fails ? "有失败" : "阶段一全部通过");
    return fails ? 1 : 0;
}
