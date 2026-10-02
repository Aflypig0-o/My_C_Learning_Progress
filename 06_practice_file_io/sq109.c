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
    p->next = prev->next;
    prev->next =p;
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

void print_list(const LinkedList *list)
{
    if(list == NULL || list->head == NULL)
    {
        fprintf(stderr,"未初始化");
        return;
    }
    const Node *p = list->head->next;
    while(p != NULL)
    {
        printf("%d -> ",p->data);
        p = p->next;
    }
    printf(" NULL (size = %zu)\n",list->size);
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
        return NULL;
    }
    Node *p = list->head->next;
    while(p != NULL)
    {
        if(p->data = NULL)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

bool modify_by_index(LinkedList *list,size_t index,int new_value)
{
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
    if(list == NULL || list->head == NULL || index >= list->size)
    {
        return false;
    }
    Node *prev = list->head;
    for(size_t i = 0;i<index;++i)
    {
        prev = prev->next;
    }
    Node *p = prev->next;
    prev->next = p->next;
    if(list->tail == p)
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
    while (p != NULL && p->data != value)
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


void list_save_to_file(LinkedList *list,const char *filename)
{
    if(list == NULL || list->head == NULL)
    {
        return;
    }
    FILE *fp = fopen(filename,"w");
    if(fp == NULL)
    {
        perror("fopen");
        return;
    }
    Node *p = list->head->next;
    while(p != NULL)
    {
        fprintf(fp,"%d\n",p->data);
        p = p->next;
    }
    fclose(fp);
    printf("已经保存%zu个节点到%s\n",list->size,filename);
}

void list_load_from_file(LinkedList *list,const char *filename)
{
    if(list == NULL || list->head == NULL)
    {
        return;
    }
    FILE *fp = fopen(filename,"r");
    if(fp == NULL)
    {
        perror("fopen");
        return;
    }
    int value;
    while(fscanf(fp,"%d",&value)==1)
    {
        insertTail(list,value);
    }
    fclose(fp);
    printf("已从 %s 读取 %zu 个节点\n", filename, list->size);
}



int main()
{
    LinkedList list;
    LinkedList list1;
    initList(&list1);
    insertTail(&list1, 10);
    insertTail(&list1, 20);
    insertTail(&list1, 30);
    insertTail(&list1, 40);
    insertTail(&list1, 50);
    
    printf("原链表：");
    printList(&list1);
    
    list_save_to_file(&list1, "list.txt");
    destroyList(&list1);
    
    LinkedList list2;
    initList(&list2);
    list_load_from_file(&list2, "list.txt");
    
    printf("恢复的链表：");
    printList(&list2);
    
    destroyList(&list2);
    return 0;
}
