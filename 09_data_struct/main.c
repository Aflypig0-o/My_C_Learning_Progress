#include <stdio.h>
#include "dlist.h"

int main() {
    printf("========== 测试开始 ==========\n");

    // 1. 创建链表
    DLinkedList *list = create_list();
    if (list == NULL) {
        printf("链表创建失败！\n");
        return 1;
    }
    printf("1. 链表创建成功。\n");

    // 2. 测试空链表打印
    printf("\n[测试项] 空链表状态：\n");
    printf("正向: ");
    list->print_forward(list);  // 预期：什么都不打印，直接换行
    printf("反向: ");
    list->print_backward(list); // 预期：什么都不打印，直接换行

    // 3. 测试空链表删除（极其容易发生段错误的地方）
    printf("\n[测试项] 尝试从空链表删除节点：\n");
    list->pop_back(list);       // 预期：被 size == 0 拦截，安全退出，不崩溃
    printf("空链表删除安全通过。\n");

    // 4. 插入数据
    printf("\n[测试项] 插入 10, 20, 30：\n");
    list->push_back(list, 10);
    list->push_back(list, 20);
    list->push_back(list, 30);
    printf("正向: ");
    list->print_forward(list);  // 预期：10 20 30
    printf("反向: ");
    list->print_backward(list); // 预期：30 20 10

    // 5. 删除尾部数据
    printf("\n[测试项] 连续删除两次尾部：\n");
    list->pop_back(list);
    list->pop_back(list);
    printf("正向: ");
    list->print_forward(list);  // 预期：10
    printf("反向: ");
    list->print_backward(list); // 预期：10-

    // 6. 删空并重新插入
    printf("\n[测试项] 删光所有节点再重新插入：\n");
    list->pop_back(list);       // 删掉 10
    list->push_back(list, 99);  // 重新插一个 99
    printf("正向: ");
    list->print_forward(list);  // 预期：99
    printf("反向: ");
    list->print_backward(list); // 预期：99

    // 7. 销毁链表
    printf("\n[测试项] 销毁链表：\n");
    list->destroy(list);
    list = NULL;                // 防御性置空
    printf("链表已销毁，未发生崩溃。\n");

    printf("\n========== 测试完美通过 ==========\n");
    return 0;
}