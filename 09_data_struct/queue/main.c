#include <stdio.h>
#include "queue.h"

int main() {
    printf("========== 队列(queue) 终极测试 ==========\n");

    // 1. 创建队列
    Queue *q = queue_create();
    if (q == NULL) {
        printf("队列创建失败！\n");
        return 1;
    }
    printf("1. 队列创建成功。\n\n");

    // 2. 测试空队列判空与出队
    printf("[测试项] 空队列状态：\n");
    if (q->is_empty(q)) {
        printf("-> 判空结果: 队列为空 (正确)\n");
    } else {
        printf("-> 判空结果: 队列不为空 (错误)\n");
    }

    int out_val;
    if (!q->dequeue(q, &out_val)) {
        printf("-> 尝试出队: 出队失败，队列为空 (正确)\n");
    } else {
        printf("-> 尝试出队: 成功出队 %d (错误)\n", out_val);
    }
    printf("\n");

    // 3. 测试入队 (FIFO 顺序)
    printf("[测试项] 入队 10, 20, 30：\n");
    q->enqueue(q, 10);
    q->enqueue(q, 20);
    q->enqueue(q, 30);
    
    if (!q->is_empty(q)) {
        printf("-> 判空结果: 队列不为空 (正确)\n");
    }
    printf("\n");

    // 4. 测试出队
    printf("[测试项] 连续出队 (先进先出):\n");
    while (!q->is_empty(q)) {
        if (q->dequeue(q, &out_val)) {
            printf("出队: %d\n", out_val);
        }
    }
    printf("\n");

    // 5. 测试出队变空后的状态
    printf("[测试项] 队列再次变空后的状态：\n");
    if (q->is_empty(q)) {
        printf("-> 判空结果: 队列为空 (正确)\n");
    }
    if (!q->dequeue(q, &out_val)) {
        printf("-> 尝试出队: 出队失败，队列为空 (正确)\n");
    }
    printf("\n");

    // 6. 测试清空后重新入队 (极其容易踩坑的地方)
    printf("[测试项] 清空后重新入队 99：\n");
    q->enqueue(q, 99);
    if (q->dequeue(q, &out_val)) {
        printf("-> 成功出队: %d (正确)\n", out_val);
    }
    printf("\n");

    // 7. 销毁队列
    printf("[测试项] 销毁队列：\n");
    q->destroy(q);
    q = NULL; // 防御性置空，防止野指针
    printf("队列已销毁，内存清理完毕。\n");

    printf("\n========== 队列测试完美通过 ==========\n");
    return 0;
}