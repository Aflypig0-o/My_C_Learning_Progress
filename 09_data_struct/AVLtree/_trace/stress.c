#include <stdio.h>
#include <stdlib.h>
#include "AVLtree.h"

static int cnt(AVLNode *n) { return n ? 1 + cnt(n->left) + cnt(n->right) : 0; }

static int chk_bst(AVLNode *n, int *p, int *f)
{
    if (!n) return 1;
    if (!chk_bst(n->left, p, f)) return 0;
    if (!*f && n->data <= *p) return 0;
    *f = 0;
    *p = n->data;
    return chk_bst(n->right, p, f);
}

static int chk_avl(AVLNode *n)
{
    if (!n) return 1;
    int bf = n->get_balance(n);
    if (bf > 1 || bf < -1) return 0;
    int lh = n->get_height(n->left), rh = n->get_height(n->right);
    if (n->height != (lh > rh ? lh : rh) + 1) return 0;
    return chk_avl(n->left) && chk_avl(n->right);
}

static int ok(AVLNode *r)
{
    int p = 0, f = 1;
    return chk_bst(r, &p, &f) && chk_avl(r);
}

int main(void)
{
    int fails = 0;

    /* A. 满树删到空：顺序插入 1..1023，再随机顺序全删 */
    {
        int N = 1023;
        int *v = malloc(sizeof(int) * N);
        for (int i = 0; i < N; i++) v[i] = i + 1;

        AVLNode *r = NULL;
        for (int i = 0; i < N; i++) r = insert(r, v[i]);
        printf("[A] 插入 1..%d: 高=%d 节点=%d %s\n",
               N, r ? r->get_height(r) : -1, cnt(r), ok(r) ? "OK" : "FAIL");
        if (!ok(r)) fails++;

        srand(7);
        int good = 1;
        for (int i = N - 1; i > 0; i--)
        {
            int j = rand() % (i + 1);
            int t = v[i]; v[i] = v[j]; v[j] = t;
        }
        for (int i = 0; i < N && good; i++)
        {
            r = avl_delete(r, v[i]);
            if (!ok(r)) { printf("    删 %d 后失效\n", v[i]); good = 0; }
        }
        printf("[A] 随机顺序全删: %s 最终=%p\n", good ? "OK" : "FAIL", (void*)r);
        if (!good) fails++;
        free(v);
    }

    /* B. 只用左分支的退化序列删中间 */
    {
        AVLNode *r = NULL;
        for (int i = 1; i <= 100; i++) r = insert(r, i);
        int good = 1;
        for (int i = 50; i >= 1 && good; i -= 3)
        {
            r = avl_delete(r, i);
            if (!ok(r)) good = 0;
        }
        for (int i = 51; i <= 100 && good; i += 3)
        {
            r = avl_delete(r, i);
            if (!ok(r)) good = 0;
        }
        printf("[B] 交错删除: %s 剩余=%d\n", good ? "OK" : "FAIL", cnt(r));
        if (!good) fails++;
        if (r) r->destroy(r);
    }

    /* C. 删除根节点反复 */
    {
        AVLNode *r = NULL;
        for (int i = 1; i <= 30; i++) r = insert(r, i * 2);
        int good = 1;
        for (int k = 0; k < 30 && good; k++)
        {
            r = avl_delete(r, r->data);      /* 每次删当前根 */
            if (r && !ok(r)) good = 0;
        }
        printf("[C] 连续删除根节点: %s 最终=%p\n", good ? "OK" : "FAIL", (void*)r);
        if (!good) fails++;
    }

    /* D. 极端：插 1..500 再从 500 删到 1（逆序删） */
    {
        AVLNode *r = NULL;
        for (int i = 1; i <= 500; i++) r = insert(r, i);
        int good = 1;
        for (int i = 500; i >= 1 && good; i--)
        {
            r = avl_delete(r, i);
            if (!ok(r)) good = 0;
        }
        printf("[D] 逆序删除 500 个: %s 最终=%p\n", good ? "OK" : "FAIL", (void*)r);
        if (!good) fails++;
    }

    printf("\n=== %s ===\n", fails == 0 ? "全部通过" : "有失败项");
    return fails ? 1 : 0;
}
