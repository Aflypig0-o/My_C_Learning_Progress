#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

    Node *p = (Node*)malloc(sizeof(Node));
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
        return insertHead(&list,value);
    }
    if(index == list->size)
    {
        return insertTail(&list,value);
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

Node *find_by_index(LinkedList *list,size_t index)
{
    if(list == NULL || list->head == NULL)
    {
        fprintf(stderr,"列表无效");
        return NULL;
    }
    if(index >= list->size)
    {
        fprintf(stderr,"查找范围错误");
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
        fprintf(stderr,"列表无效");
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
        return NULL;
    }
    p->data = new_value;
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

int main()
{
    ;
}