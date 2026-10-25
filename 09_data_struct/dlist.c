#include <stdio.h>
#include "dlist.h"

static void push_back_impl(DLinkedList *self,int val)
{
    if(self == NULL)
    {
        return;
    }
    DNode *new_dnode = (DNode*)malloc(sizeof(DNode));
    if(new_dnode == NULL)
    {
        perror("malloc");
        return;
    }
    DNode *old_dnode = self->tail->prev;
    new_dnode->data = val;
    new_dnode->prev = old_dnode;
    new_dnode->next = self->tail;
    old_dnode->next = new_dnode;
    self->tail->prev = new_dnode;
    self->size++;
}

static void pop_back_impl(DLinkedList *self)
{
    if(self == NULL || self->size == 0)
    {
        return;
    }
    DNode *old_tail = self->tail;
    self->tail = old_tail->prev;
    self->tail->next = NULL;
    free(old_tail);
    self->size--;
}

static void print_forward_impl(DLinkedList *self)
{
    if(self == NULL)
    {
        return;
    }
    printf("NULL -> ");
    DNode *current = self->head->next;
    while(current != self->tail)
    {
        printf("%d -> ",current->data);
        current = current->next;
    }
    printf("NULL\n");
}

static void print_backward_impl(DLinkedList *self)
{
    if(self == NULL)
    {
        return;
    }
    DNode *current = self->tail->prev;
    printf("NULL -> ");
    while(current != self->head)
    {
        printf("%d -> ",current->data);
        current = current->prev;
    }
    printf("\n");
}

static void destory_impl(DLinkedList *self)
{
    if(self == NULL)
    {
        return;
    }
    DNode *current = self->head->next;
    while(current != NULL)
    {
        DNode *temp = current;
        current = current->next;
        free(temp);
    }

}

DLinkedList *create_list()
{
    DLinkedList *dlist = (DLinkedList*)malloc(sizeof(DLinkedList));
    if(dlist == NULL)
    {
        perror("malloc");
        return NULL;
    }
    DNode *head_dummy = (DNode*)malloc(sizeof(DNode));
    if(head_dummy == NULL)
    {
        perror("malloc");
        free(dlist);
        return NULL;
    }
    DNode *tail_dummy = (DNode*)malloc(sizeof(DNode));
    if(tail_dummy == NULL)
    {
        perror("malloc");
        free(head_dummy);
        free(dlist);
        return NULL;
    }
    head_dummy->data = 0;
    head_dummy->next = tail_dummy;
    head_dummy->prev = NULL;
    tail_dummy->data = 0;
    tail_dummy->next = NULL;
    tail_dummy->prev = head_dummy;

    //绑定
    dlist->head = head_dummy;
    dlist->tail = tail_dummy;
    dlist->push_back = push_back_impl;
    dlist->pop_back = pop_back_impl;
    dlist->print_forward = print_forward_impl;
    dlist->print_backward = print_backward_impl;
    dlist->destroy = destory_impl;
    return dlist;
}