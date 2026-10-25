#ifndef DLIST_H
#define DLIST_H
#include <stdlib.h>

typedef struct DNode
{
    int data;
    DNode *next;
    DNode *prev;
}DNode;

typedef struct DLinkedList
{
    DNode *head;
    DNode *tail;
    size_t size;
    void (*push_back)(DLinkedList *self, int val);
    void (*pop_back)(DLinkedList *self);
    void (*print_forward)(DLinkedList *self);
    void (*print_backward)(DLinkedList *self);
    void (*destroy)(DLinkedList *self); 
}DLinkedList;

DLinkedList *create_list();

#endif