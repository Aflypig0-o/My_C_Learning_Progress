#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>
#include "contact.h"

typedef struct Node
{
    Contact data;
    struct Node *next;
}Node;

typedef struct
{
    Node *head;
    Node *tail;
    size_t size;
}LinkedList;

bool list_init(LinkedList *list);

void list_destroy(LinkedList *list);

bool list_push_back(LinkedList *list,Contact c);

Node *list_find_by_name(LinkedList *list,const char *name);

Node *list_find_by_phone(LinkedList *list,const char *phone);

bool list_remove_by_name(LinkedList *list,const char *name);

bool list_remove_by_phone(LinkedList *list,const char *phone);

void list_print(LinkedList *list);

#endif