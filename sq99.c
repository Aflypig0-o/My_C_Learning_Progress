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

bool initlist(LinkedList *list)
{
    if(list == NULL)
    {
        return false;
    }
    Node *head =(Node*)malloc(sizeof(Node));
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

void destroyList(LinkedList *list)
{
    if(list == NULL || list->head == NULL)
    {
        return;
    }

    Node *p = list->head;
    while(p!=NULL)
    {
        Node *temp = p;
        p = p->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

Node *createNode(int value)
{
    Node *p =(Node*)malloc(sizeof(Node));
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
    if(list->tail == list->head)
    {
        list->tail = p;
    }
    ++(list->size);
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
    ++(list->size);
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
    Node *p =createNode(value);
    if(p == NULL)
    {
        return  false;
    }
    p->next = prev->next;
    prev->next = p;
    list->size++;
    return true;
}

void printList(const LinkedList *list)
{
    if(list == NULL || list->head == NULL)
    {
        printf("未初始化");
        return;
    }
    for(const Node *p =list->head->next;p!=NULL;p=p->next)
    {
        printf("%d -> ",p->data);
    }
    printf("NULL (size = %zu)",list->size);
}

int main()
{
    LinkedList list;
    if(!initlist(&list))
    {
        return EXIT_FAILURE;
    }
    for(int i=100;i<400;i+=100)
    {
        insertTail(&list,i);
    }
    printList(&list);
    destroyList(&list);
    return 0;
}