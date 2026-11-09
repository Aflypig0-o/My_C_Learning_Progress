#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rbtree.h"

static int count_nodes(RBNode *n)
{
    if (n == NULL) return 0;
    return 1 + count_nodes(n->left) + count_nodes(n->right);
}

static int tree_height(RBNode *n)
{
    if (n == NULL) return 0;
    int l = tree_height(n->left), r = tree_height(n->right);
    return (l > r ? l : r) + 1;
}

/* ---------------- 演示 ---------------- */

static void demo(void)
{
    RBNode *root = NULL;
    int vals[] = {10, 20, 30, 15, 25, 5, 1, 40, 50, 35, 45};

    printf("=== 演示：插入 ===\n");
    for (int i = 0; i < (int)(sizeof(vals) / sizeof(vals[0])); i++)
        root = rb_insert(root, vals[i]);

    printf("中序: ");
    rb_dump_inorder(root);
    printf("\n校验: %s  黑高=%d  节点=%d  树高=%d\n\n",
           rb_check(root) ? "OK" : "FAIL",
           rb_black_height(root), count_nodes(root), tree_height(root));

    printf("=== 演示：删除 ===\n");
    int dels[] = {20, 30, 1, 50, 10};
    for (int i = 0; i < (int)(sizeof(dels) / sizeof(dels[0])); i++)
    {
        root = rb_delete(root, dels[i]);
        printf("删 %2d → 中序: ", dels[i]);
        rb_dump_inorder(root);
        printf("\n      校验: %s 黑高=%d 节点=%d\n",
               rb_check(root) ? "OK" : "FAIL",
               rb_black_height(root), count_nodes(root));
    }

    printf("\n删不存在的 999: %s\n",
           rb_delete(root, 999) == root ? "根不变 OK" : "FAIL");

    rb_destroy(root);
}

/* ---------------- 随机测试：插入 + 删除 ---------------- */

static int random_test(void)
{
    srand(20261109);

    for (int round = 0; round < 300; round++)
    {
        RBNode *root = NULL;
        int live[400];
        int nlive = 0;

        for (int step = 0; step < 500; step++)
        {
            if (rand() % 3 != 0)                 /* 2/3 插入 */
            {
                int v = rand() % 300;
                int existed = 0;
                for (int k = 0; k < nlive; k++)
                    if (live[k] == v) { existed = 1; break; }

                int before = count_nodes(root);
                root = rb_insert(root, v);
                if (!existed) live[nlive++] = v;

                int expect = before + (existed ? 0 : 1);
                if (!rb_check(root) || count_nodes(root) != expect)
                {
                    printf("FAIL insert round=%d step=%d v=%d\n", round, step, v);
                    return 0;
                }
            }
            else if (nlive > 0)                  /* 1/3 删除 */
            {
                int idx = rand() % nlive;
                int v = live[idx];
                int before = count_nodes(root);

                root = rb_delete(root, v);
                live[idx] = live[--nlive];

                if (!rb_check(root) || count_nodes(root) != before - 1)
                {
                    printf("FAIL delete round=%d step=%d v=%d\n", round, step, v);
                    return 0;
                }
            }
        }

        /* 一轮结束：把剩下的全部删空，检查能删干净 */
        while (nlive > 0)
        {
            int idx = rand() % nlive;
            int v = live[idx];
            root = rb_delete(root, v);
            live[idx] = live[--nlive];
            if (!rb_check(root)) { printf("FAIL drain\n"); return 0; }
        }
        if (root != NULL) { printf("FAIL not empty\n"); return 0; }

        rb_destroy(root);
    }
    return 1;
}

/* ---------------- 顺序插入 / 顺序删除 ---------------- */

static int sequential_test(void)
{
    RBNode *root = NULL;
    int n = 2000;

    for (int i = 1; i <= n; i++)
        root = rb_insert(root, i);
    if (!rb_check(root)) { printf("FAIL 顺序插入\n"); return 0; }
    printf("顺序插入 1..%d: 树高=%d\n", n, tree_height(root));

    for (int i = 1; i <= n; i++)
    {
        root = rb_delete(root, i);
        if (!rb_check(root)) { printf("FAIL 顺序删除 i=%d\n", i); return 0; }
    }
    if (root != NULL) { printf("FAIL 未删空\n"); return 0; }
    printf("顺序删除 1..%d: 全部通过，树已空\n", n);
    return 1;
}

int main(void)
{
    demo();

    printf("\n=== 随机测试 ===\n");
    if (random_test())
        printf("300 轮 x 500 次混合插入/删除，每步校验五性质 + 节点数：全部通过\n");
    else
        return 1;

    printf("\n=== 顺序测试 ===\n");
    if (!sequential_test()) return 1;

    printf("\n全部测试通过\n");
    return 0;
}
