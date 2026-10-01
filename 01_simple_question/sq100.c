#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

typedef struct
{
    Node *head;
    Node *tail;
    size_t size;
}LinkedList;

bool initList(LinkedList *list)
{
    if(list == NULL)
    {
        return false;
    }
    Node *head = (Node*)malloc(sizeof(Node));
    if(head == NULL)
    {
        perror("malloc");
        return false;
    }
    head->data = 0;
    head->next = NULL;
    list->head = head;
    list->tail = head;
    list->size = 0;
    return true;
}

Node *createNode(int value)
{
    Node *p = (Node*)malloc(sizeof(Node));
    if(p == NULL)
    {
        perror("malloc");
        return NULL;
    }
    p->data = value;
    p->next = NULL;
    return p;
}

bool insertHead(LinkedList *list,int value)
{
    if(list == NULL || list->head == NULL)
    {
        return false;
    }
    Node *p = createNode(value);
    if(p == NULL)
    {
        return false;
    }
    p->next = list->head->next;
    list->head->next = p;
    if(list->head == list->tail)
    {
        list->tail = p;
    }
    list->size++;
    return true;
}

bool insertTail(LinkedList *list,int value)
{
    if(list == NULL || list->head == NULL)
    {
        return false;
    }
    Node *p = createNode(value);
    if(p == NULL)
    {
        return false;
    }
    list->tail->next = p;
    list->tail = p;
    list->size++;
    return true;
}

bool insertAt(LinkedList *list,size_t index,int value)
{
    if(list == NULL || list->head == NULL)
    {
        return false;
    }
    if(index > list->size)
    {
        return false;
    }
    if(index == 0)
    {
        return insertHead(list,value);
    }
    if(index == list->size)
    {
        return insertTail(list,value);
    }
    Node *prev = list->head;

    for(size_t i=0;i<index;++i)
    {
        prev = prev->next;
    }
    Node *p = createNode(value);
    if(p == NULL)
    {
        return false;
    }
    p->next = prev->next;
    prev->next = p;
    list->size++;
    return true;
}

void destroyList(LinkedList *list)
{
    if(list == NULL || list->head == NULL)
    {
        return;
    }
    Node *p = list->head;
    while(p != NULL)
    {
        Node *temp = p;
        p = p->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void printList(const LinkedList *list)
{
    if(list == NULL || list->head == NULL)
    {
        printf("未初始化");
        return;
    }
    const Node *p = list->head->next;
    while(p != NULL)
    {
        printf("%d -> ",p->data);
        p = p->next;
    }
    printf("NULL (size = %zu)\n",list->size);
}

Node *find_by_index(LinkedList *list,size_t index)
{
    if(list == NULL || list->head == NULL)
    {
        return NULL;
    }
    if(index >= list->size)
    {
        return NULL;
    }
    Node *p = list->head->next;
    for(size_t i=0;i<index;++i)
    {
        p = p->next;
    }
    return p;
}

Node *find_by_value(LinkedList *list,int value)
{
    if(list == NULL || list->head == NULL)
    {
        fprintf(stderr,"列表无效\n");
        return NULL;
    }

    Node *p = list->head->next;
    while(p != NULL)
    {
        if(p->data == value)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

bool modify_by_index(LinkedList *list,size_t index,int new_value)
{
    //此处已经有检查
    Node *p = find_by_index(list,index);
    if(p == NULL)
    {
        return false;
    }
    p->data = new_value;
    return true;
}

bool modify_by_value(LinkedList *list,int value,int new_value)
{
    Node *p = find_by_value(list,value);
    if(p == NULL)
    {
        return false;
    }
    p->data = new_value;
    return true;
}

bool delete_by_index(LinkedList *list,size_t index)
{
    if(list == NULL || list->head == NULL || index>=list->size)
    {
        return false;
    }
    Node *prev = list->head;
    for(size_t i=0;i<index;++i)
    {
        prev = prev->next;
    }
    Node *p = prev->next;
    prev->next = p->next;
    if(p == list->tail)
    {
        list->tail = prev;
    }
    free(p);
    list->size--;
    return true;
}

bool delete_by_value(LinkedList *list,int value)
{
    if(list == NULL || list->head == NULL)
    {
        return false;
    }
    Node *p = list->head->next;
    Node *prev = list->head;
    while(p != NULL && p->data != value)
    {
        prev = p;
        p = p->next;
    }
    if(p == NULL)
    {
        return false;
    }
    prev->next = p->next;
    if(p == list->tail)
    {
        list->tail = prev;
    }
    free(p);
    list->size--;
    return true;
}
    int main()
{
    LinkedList list;
    
    // ========== 1. 初始化 ==========
    printf("===== 1. 初始化 =====\n");
    if (!initList(&list)) {
        printf("初始化失败\n");
        return EXIT_FAILURE;
    }
    printf("初始化成功\n");
    printList(&list);   // 空链表


    // ========== 2. 插入测试 ==========
    printf("\n===== 2. 插入测试 =====\n");
    
    // 尾插：10, 20, 30
    printf("尾插 10, 20, 30:\n");
    insertTail(&list, 10);
    insertTail(&list, 20);
    insertTail(&list, 30);
    printList(&list);   // 10 -> 20 -> 30 -> NULL (size = 3)
    
    // 头插：5
    printf("头插 5:\n");
    insertHead(&list, 5);
    printList(&list);   // 5 -> 10 -> 20 -> 30 -> NULL (size = 4)
    
    // 指定位置插入：在下标 2 处插入 99
    printf("在下标 2 处插入 99:\n");
    insertAt(&list, 2, 99);
    printList(&list);   // 5 -> 10 -> 99 -> 20 -> 30 -> NULL (size = 5)
    
    // 边界：下标 0 插入
    printf("在下标 0 处插入 1:\n");
    insertAt(&list, 0, 1);
    printList(&list);   // 1 -> 5 -> 10 -> 99 -> 20 -> 30 -> NULL (size = 6)
    
    // 边界：下标 = size 插入（等于尾插）
    printf("在下标 6 (size) 处插入 88:\n");
    insertAt(&list, 6, 88);
    printList(&list);   // 1 -> 5 -> 10 -> 99 -> 20 -> 30 -> 88 -> NULL (size = 7)
    
    // 非法：下标越界
    printf("在下标 100 处插入 777 (应该失败):\n");
    if (insertAt(&list, 100, 777)) {
        printf("插入成功 (异常!)\n");
    } else {
        printf("插入失败 (符合预期)\n");
    }


    // ========== 3. 查找测试 ==========
    printf("\n===== 3. 查找测试 =====\n");
    
    // 按下标查找
    Node *p1 = find_by_index(&list, 3);
    if (p1 != NULL) {
        printf("下标 3 的值: %d (期望 99)\n", p1->data);
    }
    
    // 按值查找
    Node *p2 = find_by_value(&list, 20);
    if (p2 != NULL) {
        printf("找到 20\n");
    }
    
    Node *p3 = find_by_value(&list, 999);
    if (p3 == NULL) {
        printf("999 不存在 (符合预期)\n");
    }


    // ========== 4. 修改测试 ==========
    printf("\n===== 4. 修改测试 =====\n");
    
    // 按下标修改：下标 1 改成 55
    printf("将下标 1 (原值 5) 改成 55:\n");
    modify_by_index(&list, 1, 55);
    printList(&list);
    
    // 按值修改：把 99 改成 100
    printf("将值 99 改成 100:\n");
    modify_by_value(&list, 99, 100);
    printList(&list);
    
    // 修改不存在的值
    printf("将值 999 改成 0 (应该失败):\n");
    if (modify_by_value(&list, 999, 0)) {
        printf("修改成功 (异常!)\n");
    } else {
        printf("修改失败 (符合预期)\n");
    }


    // ========== 5. 删除测试 ==========
    printf("\n===== 5. 删除测试 =====\n");
    
    // 按下标删除：删下标 0（头节点）
    printf("删除下标 0 (原值 1):\n");
    delete_by_index(&list, 0);
    printList(&list);
    
    // 按下标删除：删下标 1（中间节点）
    printf("删除下标 1:\n");
    delete_by_index(&list, 1);
    printList(&list);
    
    // 按下标删除：删最后一个（尾节点）
    printf("删除最后一个节点 (下标 = size-1):\n");
    delete_by_index(&list, list.size - 1);
    printList(&list);
    
    // 按值删除
    printf("按值删除 88:\n");
    delete_by_value(&list, 88);
    printList(&list);
    
    // 删除不存在的值
    printf("按值删除 999 (应该失败):\n");
    if (delete_by_value(&list, 999)) {
        printf("删除成功 (异常!)\n");
    } else {
        printf("删除失败 (符合预期)\n");
    }


    // ========== 6. 边界测试 ==========
    printf("\n===== 6. 边界测试 =====\n");
    
    // 清空链表（逐个删）
    printf("清空链表:\n");
    while (list.size > 0) {
        delete_by_index(&list, 0);
    }
    printList(&list);   // 空链表
    
    // 空链表删除
    printf("空链表删除 (应该失败):\n");
    if (delete_by_index(&list, 0)) {
        printf("删除成功 (异常!)\n");
    } else {
        printf("删除失败 (符合预期)\n");
    }
    
    // 空链表查找
    printf("空链表查找 (应该返回 NULL):\n");
    if (find_by_index(&list, 0) == NULL) {
        printf("返回 NULL (符合预期)\n");
    }


    // ========== 7. 销毁 ==========
    printf("\n===== 7. 销毁链表 =====\n");
    destroyList(&list);
    printf("销毁完成\n");

    return 0;
}