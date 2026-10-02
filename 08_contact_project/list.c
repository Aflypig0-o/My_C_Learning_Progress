#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

bool list_init(LinkedList *list)
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
    head->next = NULL;
    list->head = head;
    list->tail = head;
    list->size = 0;
    return true;
}

void list_destroy(LinkedList *list)
{
    if(list == NULL)
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

bool list_push_back(LinkedList *list,Contact c)
{
    if(list == NULL || list->head == NULL)
    {
        return false;
    }
    Node *p = (Node*)malloc(sizeof(Node));
    if(p == NULL)
    {
        perror("malloc");
        return false;
    }
    p->data = c;
    p->next = NULL;

    list->tail->next = p;
    list->tail = p;
    list->size++;
    return true;
}

Node *list_find_by_name(LinkedList *list,const char *name)
{
    if(list == NULL || list->head == NULL)
    {
        return NULL;
    }
    Node *p = list->head->next;
    while(p != NULL)
    {
        if(strcmp(p->data.name,name) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

Node *list_find_by_phone(LinkedList *list,const char *phone)
{
    if(list == NULL || list->head == NULL)
    {
        return NULL;
    }
    Node *p = list->head->next;
    while(p != NULL)
    {
        if(strcmp(p->data.phone,phone) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

bool list_remove_by_name(LinkedList *list,const char *name)
{
    if(list == NULL || list->head == NULL)
    {
        return false;
    }
    Node *cur = list->head->next;
    Node *prev = list->head;
    while(cur != NULL && strcmp(cur->data.name,name) != 0)
    {
        prev = cur;
        cur = cur->next;
    }
    if(cur == NULL)
    {
        return false;
    }
    prev->next = cur->next;
    if(cur == list->tail)
    {
        list->tail = prev;
    }
    free(cur);
    list->size--;
    return true;
}

bool list_remove_by_phone(LinkedList *list,const char *phone)
{
    if(list == NULL || list->head == NULL)
    {
        return false;
    }
    Node *cur = list->head->next;
    Node *prev = list->head;
    while(cur != NULL && strcmp(cur->data.phone,phone) != 0)
    {
        prev = cur;
        cur = cur->next;
    }
    if(cur == NULL)
    {
        return false;
    }
    prev->next = cur->next;
    if(list->tail == cur)
    {
        list->tail = prev;
    }
    free(cur);
    list->size--;
    return true;
}

void list_print(LinkedList *list)
{
    if(list == NULL || list->head == NULL)
    {
        fprintf(stderr,"未初始化\n");
        return;
    }
    if(list->size == 0)
    {
        printf("通讯录为空\n");
        return;
    }
    printf("共%zu个联系人\n",list->size);
    const Node *p = list->head->next;
    size_t index = 1;
    while(p != NULL)
    {
        printf("%zu. 姓名: %s  电话: %s  年龄: %d\n",index,p->data.name,p->data.phone,p->data.age);
        p = p->next;
        ++index;
    }
}
