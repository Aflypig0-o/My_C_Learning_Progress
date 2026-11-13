#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RBtree.h"

static int cnt(RBNode *n){ return n ? 1 + cnt(n->left) + cnt(n->right) : 0; }

static int height_of(RBNode *n)
{
    if(!n) return 0;
    int l = height_of(n->left), r = height_of(n->right);
    return (l > r ? l : r) + 1;
}

int main(void)
{
    int fails = 0;

    /* 1. 教科书用例 */
    printf("=== 依次插入 10 20 30 15 25 5 1 ===\n");
    {
        RBNode *r = NULL;
        int v[] = {10,20,30,15,25,5,1};
        for(int i=0;i<7;i++) r = insert(r, v[i]);
        printf("中序: ");
        r->dump_inorder(r);
        printf("\n校验: %s  节点=%d 高=%d\n\n",
               rb_check(r)?"OK":"FAIL", cnt(r), height_of(r));
        if(!rb_check(r)) fails++;
        r->rb_destroy(r);
    }

    /* 2. 每次插入后立即校验 */
    printf("=== 每次插入后校验 ===\n");
    {
        RBNode *r = NULL;
        int v[] = {10,20,30,15,25,5,1,35,45,50,40,8,12,28,33};
        int bad = -1;
        for(int i=0;i<15;i++){
            r = insert(r, v[i]);
            if(!rb_check(r)){ bad = i; break; }
        }
        if(bad<0) printf("15 步全部 OK\n");
        else printf("第 %d 步插入 %d 失败\n", bad, v[bad]);
        if(bad>=0) fails++;
        r->rb_destroy(r);
    }

    /* 3. 顺序插入 1000 */
    {
        RBNode *r = NULL;
        for(int i=1;i<=1000;i++) r = insert(r, i);
        int ok = rb_check(r);
        printf("顺序插入 1..1000: 节点=%d 高=%d %s\n", cnt(r), height_of(r), ok?"OK":"FAIL");
        if(!ok) fails++;
        r->rb_destroy(r);
    }

    /* 4. 逆序插入 1000 */
    {
        RBNode *r = NULL;
        for(int i=1000;i>=1;i--) r = insert(r, i);
        int ok = rb_check(r);
        printf("逆序插入 1000..1: 节点=%d 高=%d %s\n", cnt(r), height_of(r), ok?"OK":"FAIL");
        if(!ok) fails++;
        r->rb_destroy(r);
    }

    /* 5. 重复值不破坏结构 */
    {
        RBNode *r = NULL;
        for(int i=0;i<100;i++) r = insert(r, 50);
        int ok = rb_check(r) && cnt(r)==1;
        printf("重复插入 50 共 100 次: 节点=%d %s\n", cnt(r), ok?"OK":"FAIL");
        if(!ok) fails++;
        r->rb_destroy(r);
    }

    /* 6. 随机压力测试 */
    printf("\n=== 随机压力测试 ===\n");
    {
        srand(20261113);
        int total = 0, bad = 0;
        for(int round=0; round<200; round++){
            RBNode *r = NULL;
            for(int i=0;i<200;i++){
                r = insert(r, rand()%500);
                total++;
                if(!rb_check(r)){ bad++; break; }
            }
            r->rb_destroy(r);
            if(bad) break;
        }
        printf("200 轮 x 200 次插入（共 %d 次），失败 %d 次 %s\n",
               total, bad, bad?"FAIL":"OK");
        if(bad) fails++;
    }

    /* 7. 刻意制造坏树，验证 rb_check 能抓到 */
    printf("\n=== 反测试：rb_check 能否抓到坏树 ===\n");
    {
        /* (a) 红根 */
        RBNode *a = rb_create(10, RED);
        printf("  (a) 红根:        %s\n", rb_check(a)?"漏报 FAIL":"抓到 OK");
        if(rb_check(a)) fails++;
        free(a);

        /* (b) 红红相邻 */
        RBNode *b = rb_create(10, RED);
        RBNode *c = rb_create(5, RED);
        b->left = c; c->parent = b;
        printf("  (b) 红红相邻:    %s\n", rb_check(b)?"漏报 FAIL":"抓到 OK");
        if(rb_check(b)) fails++;
        free(c); free(b);

        /* (c) BST 被破坏 */
        RBNode *d = rb_create(10, BLACK);
        RBNode *e = rb_create(20, BLACK);
        d->left = e; e->parent = d;
        printf("  (c) BST 违反:    %s\n", rb_check(d)?"漏报 FAIL":"抓到 OK");
        if(rb_check(d)) fails++;
        free(e); free(d);

        /* (d) 黑高不等 */
        RBNode *f = rb_create(10, BLACK);
        RBNode *g = rb_create(5, BLACK);
        RBNode *h = rb_create(15, RED);
        f->left = g; g->parent = f;
        f->right = h; h->parent = f;
        RBNode *i = rb_create(3, RED);
        g->left = i; i->parent = g;
        printf("  (d) 黑高不等:    %s\n", rb_check(f)?"漏报 FAIL":"抓到 OK");
        if(rb_check(f)) fails++;
        free(i); free(g); free(h); free(f);

        /* (e) 合法小树 */
        RBNode *j = rb_create(10, BLACK);
        printf("  (e) 单黑根:      %s\n", rb_check(j)?"OK":"误报 FAIL");
        if(!rb_check(j)) fails++;
        free(j);

        printf("  (f) 空树:        %s\n", rb_check(NULL)?"OK":"误报 FAIL");
        if(!rb_check(NULL)) fails++;
    }

    printf("\n=== %s ===\n", fails==0?"全部通过":"有失败项");
    return fails ? 1 : 0;
}
