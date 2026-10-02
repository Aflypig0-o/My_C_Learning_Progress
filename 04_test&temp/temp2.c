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
        return NULL;
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
    if(p==NULL)
    {
        return false;
    }
    p->next = list->head->next;
    list->head->next = p;
    if(list->head == list ->tail)
    {
        list->tail = p;
    }
    list->size++;
    return true;
}

bool insertTail(Linkedlist *list,int value)
{
    if(list == NULL || list->head == NULL)
    {
        return false;
    }
    Node *p =(Node*)malloc(sizeof(Node));
    if(p == NULL)
    {
        return false;
    }
    list->tail->next = p;
    list->tail = p;
    list->size++;
    return true;
}