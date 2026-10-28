#include <stdio.h>
#include "cqueue.h"

int main() {
    printf("========== 循环队列(CQueue) 终极测试 ==========\n");

    // 👈 改成 2：逻辑容量为 2，实际数组容量为 3 (浪费1个)
    CQueue *q = cqueue_create(2);
    if (q == NULL) return 1;
    printf("1. 队列创建成功 (容量2)。\n\n");

    printf("[测试项] 空队列状态：\n");
    printf("-> 是否为空: %s\n", q->is_empty(q) ? "是" : "否"); // 预期: 是
    printf("-> 队首元素: %d\n\n", q->get_front(q)); // 预期: -1

    printf("[测试项] 入队 10, 20：\n");
    q->enqueue(q, 10);
    q->enqueue(q, 20);
    
    // 此时 rear=2, front=0, capacity=3。(2+1)%3 == 0，满了！
    printf("-> 是否已满: %s\n", q->is_full(q) ? "是" : "否"); // 预期: 是
    printf("-> 尝试入队 30: %s\n\n", q->enqueue(q, 30) ? "成功" : "失败 (队列已满)"); // 预期: 失败

    printf("[测试项] 绕圈测试（验证取模魔法）：\n");
    int out_val;
    if (q->dequeue(q, &out_val)) {
        printf("-> 出队成功，拿到的值: %d\n", out_val); // 预期: 10
    }
    // 此时 front=1，有空位了
    printf("-> 再次入队 30: %s\n", q->enqueue(q, 30) ? "成功" : "失败"); // 预期: 成功
    
    // 看看 30 是不是绕回到了下标 0
    q->dequeue(q, &out_val);
    printf("-> 出队: %d\n", out_val); // 预期: 20
    q->dequeue(q, &out_val);
    printf("-> 出队: %d\n", out_val); // 预期: 30

    printf("\n[测试项] 销毁队列...\n");
    q->destroy(q);
    printf("========== 循环队列测试完美通关 ==========\n");
    return 0;
}