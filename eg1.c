#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ================= 节点 ================= */

typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* ================= 内存池 ================= */

#define BLOCK_SIZE 64   // 每个大块容纳的节点数

typedef struct Block {
    struct Block *next_block;
    Node nodes[BLOCK_SIZE];
} Block;

typedef struct NodePool {
    Block *blocks;      // 所有已申请的大块
    Node  *free_list;   // 空闲节点链表
} NodePool;

static void pool_init(NodePool *pool) {
    pool->blocks = NULL;
    pool->free_list = NULL;
}

// 一次性申请一大块，切成节点挂到 free_list
static bool pool_grow(NodePool *pool) {
    Block *b = malloc(sizeof(Block));
    if (b == NULL) {
        perror("malloc");
        return false;
    }
    b->next_block = pool->blocks;
    pool->blocks = b;

    for (size_t i = 0; i < BLOCK_SIZE; i++) {
        b->nodes[i].next = pool->free_list;
        pool->free_list = &b->nodes[i];
    }
    return true;
}

// 取一个节点 O(1)
static Node *pool_alloc(NodePool *pool) {
    if (pool->free_list == NULL) {
        if (!pool_grow(pool)) return NULL;
    }
    Node *p = pool->free_list;
    pool->free_list = p->next;
    p->next = NULL;
    return p;
}

// 还一个节点 O(1)
static void pool_free(NodePool *pool, Node *p) {
    if (p == NULL) return;
    p->next = pool->free_list;
    pool->free_list = p;
}

// 整体销毁：释放所有大块
static void pool_destroy(NodePool *pool) {
    Block *b = pool->blocks;
    while (b != NULL) {
        Block *next = b->next_block;
        free(b);
        b = next;
    }
    pool->blocks = NULL;
    pool->free_list = NULL;
}

/* ================= 链表 ================= */

typedef struct {
    Node *head;     // 头结点，不存有效数据
    Node *tail;     // 尾结点
    size_t size;
    NodePool *pool;
} LinkedList;

bool list_init(LinkedList *list, NodePool *pool) {
    if (list == NULL || pool == NULL) return false;

    Node *head = pool_alloc(pool);
    if (head == NULL) return false;
    head->data = 0;
    head->next = NULL;

    list->head = head;
    list->tail = head;
    list->size = 0;
    list->pool = pool;
    return true;
}

/* ---------- 插入 ---------- */

// 头插 O(1)
bool list_push_front(LinkedList *list, int value) {
    Node *p = pool_alloc(list->pool);
    if (p == NULL) return false;

    p->data = value;
    p->next = list->head->next;
    list->head->next = p;

    if (list->tail == list->head) list->tail = p;
    list->size++;
    return true;
}

// 尾插 O(1)
bool list_push_back(LinkedList *list, int value) {
    Node *p = pool_alloc(list->pool);
    if (p == NULL) return false;

    p->data = value;
    p->next = NULL;
    list->tail->next = p;
    list->tail = p;
    list->size++;
    return true;
}

/* ---------- 删除 ---------- */

// 按值删除第一个匹配节点
bool list_remove(LinkedList *list, int value) {
    Node *prev = list->head;
    Node *cur = list->head->next;

    while (cur != NULL && cur->data != value) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) return false;

    prev->next = cur->next;
    if (cur == list->tail) list->tail = prev;

    pool_free(list->pool, cur);
    list->size--;
    return true;
}

/* ---------- 清空 / 销毁 ---------- */

// 清空有效节点（归还池），保留头结点
void list_clear(LinkedList *list) {
    Node *p = list->head->next;
    while (p != NULL) {
        Node *next = p->next;
        pool_free(list->pool, p);
        p = next;
    }
    list->head->next = NULL;
    list->tail = list->head;
    list->size = 0;
}

// 释放头结点本身（链表作废）
void list_destroy(LinkedList *list) {
    if (list->head == NULL) return;
    pool_free(list->pool, list->head);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/* ---------- 打印 ---------- */

void list_print(const LinkedList *list) {
    if (list->head == NULL) {
        printf("(destroyed)\n");
        return;
    }
    for (const Node *p = list->head->next; p != NULL; p = p->next) {
        printf("%d -> ", p->data);
    }
    printf("NULL (size=%zu)\n", list->size);
}

/* ================= 算法操作 ================= */

/* ---------- reverse：原地反转 ---------- */

void list_reverse(LinkedList *list) {
    if (list->size <= 1) return;

    Node *prev = NULL;
    Node *cur = list->head->next;
    Node *old_first = cur;   // 反转后成为尾节点

    while (cur != NULL) {
        Node *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    list->head->next = prev;
    list->tail = old_first;
}

/* ---------- concat：O(1) 拼接（不要求有序） ---------- */

void list_concat(LinkedList *dst, LinkedList *src) {
    if (dst == src || src->size == 0) return;

    dst->tail->next = src->head->next;
    dst->tail = src->tail;
    dst->size += src->size;

    // 清空 src（节点已转移，不归还池）
    src->head->next = NULL;
    src->tail = src->head;
    src->size = 0;
}

/* ---------- merge：合并两个有序链表，保持升序 ---------- */

void list_merge(LinkedList *dst, LinkedList *src) {
    if (dst == src || src->size == 0) return;

    Node *a = dst->head->next;
    Node *b = src->head->next;
    Node *tail = dst->head;

    while (a != NULL && b != NULL) {
        if (a->data <= b->data) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    if (a != NULL) {
        // 剩下的是 dst 原节点，dst->tail 不变
        tail->next = a;
    } else {
        // 剩下的是 src 节点，尾指针指向 src->tail
        tail->next = b;
        dst->tail = src->tail;
    }

    dst->size += src->size;

    src->head->next = NULL;
    src->tail = src->head;
    src->size = 0;
}

/* ---------- sort：自底向上归并排序，O(1) 额外空间 ---------- */

// 对以 list 为头结点的节点序列排序，返回新的第一个节点
// 说明：不依赖 size，纯指针操作
static Node *merge_sort_nodes(Node *list) {
    if (list == NULL || list->next == NULL) return list;

    size_t insize = 1;   // 当前有序段长度

    while (1) {
        Node *p = list;
        list = NULL;
        Node *tail = NULL;
        size_t nmerges = 0;   // 本轮合并次数

        while (p != NULL) {
            nmerges++;

            // 找第一段：p 开始，长度至多 insize
            Node *q = p;
            size_t psize = 0;
            for (size_t i = 0; i < insize; i++) {
                psize++;
                q = q->next;
                if (q == NULL) break;
            }

            // 第二段：q 开始，长度至多 insize
            size_t qsize = insize;

            // 归并两段
            while (psize > 0 || (qsize > 0 && q != NULL)) {
                Node *e;
                if (psize == 0) {
                    e = q; q = q->next; qsize--;
                } else if (qsize == 0 || q == NULL) {
                    e = p; p = p->next; psize--;
                } else if (p->data <= q->data) {
                    e = p; p = p->next; psize--;
                } else {
                    e = q; q = q->next; qsize--;
                }

                if (tail != NULL) tail->next = e;
                else list = e;
                tail = e;
            }

            p = q;
        }
        tail->next = NULL;

        if (nmerges <= 1) return list;  // 本轮只合并一次，已有序
        insize *= 2;
    }
}

void list_sort(LinkedList *list) {
    if (list->size <= 1) return;

    Node *new_first = merge_sort_nodes(list->head->next);
    list->head->next = new_first;

    // 重找尾指针
    Node *p = list->head;
    while (p->next != NULL) p = p->next;
    list->tail = p;
}

/* ================= 测试 ================= */

static void build_sorted(LinkedList *l, const int *arr, size_t n) {
    for (size_t i = 0; i < n; i++) list_push_back(l, arr[i]);
}

int main(void) {
    NodePool pool;
    pool_init(&pool);

    /* ---------- 测试 1：基本插入 / 删除 / reverse ---------- */
    LinkedList a;
    list_init(&a, &pool);

    list_push_back(&a, 10);
    list_push_back(&a, 20);
    list_push_back(&a, 30);
    list_push_front(&a, 5);
    printf("a: "); list_print(&a);     // 5 10 20 30

    list_remove(&a, 20);
    printf("a: "); list_print(&a);     // 5 10 30

    list_reverse(&a);
    printf("a: "); list_print(&a);     // 30 10 5

    /* ---------- 测试 2：sort ---------- */
    LinkedList b;
    list_init(&b, &pool);
    int data[] = {42, 7, 19, 3, 88, 25, 1, 56, 14, 9};
    build_sorted(&b, data, sizeof(data) / sizeof(data[0]));
    printf("b 排序前: "); list_print(&b);
    list_sort(&b);
    printf("b 排序后: "); list_print(&b);

    /* ---------- 测试 3：merge 两个有序链表 ---------- */
    LinkedList x, y;
    list_init(&x, &pool);
    list_init(&y, &pool);

    int dx[] = {1, 3, 5, 7, 9};
    int dy[] = {2, 4, 6, 8, 10};
    build_sorted(&x, dx, sizeof(dx) / sizeof(dx[0]));
    build_sorted(&y, dy, sizeof(dy) / sizeof(dy[0]));

    printf("x: "); list_print(&x);
    printf("y: "); list_print(&y);

    list_merge(&x, &y);
    printf("x merge y: "); list_print(&x);
    printf("y after merge: "); list_print(&y);

    /* ---------- 测试 4：concat ---------- */
    LinkedList p, q;
    list_init(&p, &pool);
    list_init(&q, &pool);
    list_push_back(&p, 100);
    list_push_back(&p, 200);
    list_push_back(&q, 300);
    list_push_back(&q, 400);
    list_concat(&p, &q);
    printf("p concat q: "); list_print(&p);

    /* ---------- 清理 ---------- */
    list_clear(&a);
    list_clear(&b);
    list_clear(&x);
    list_clear(&p);

    list_destroy(&a);
    list_destroy(&b);
    list_destroy(&x);
    list_destroy(&y);
    list_destroy(&p);
    list_destroy(&q);

    pool_destroy(&pool);
    return 0;
}