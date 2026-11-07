#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

static unsigned int hash_func(const char *key,int capacity)
{
    unsigned int hash_val = 0;
    while(*key)
    {
        hash_val = hash_val * 31 + (unsigned char) *key;
        key++;
    }
    return hash_val % capacity;
}

static void put_impl(hash_table *self,const char *key,const char *value)
{
    if(self == NULL)
    {
        return;
    }
    unsigned int index = hash_func(key,self->capacity);
    hash_node *curr = self->buckets[index];
    while(curr != NULL)
    {
        if(strcmp(curr->key,key) == 0)
        {
            strcpy(curr->value,value);
            return;
        }
        curr = curr->next;
    }
    hash_node *new_node = (hash_node*)malloc(sizeof(hash_node));
    if(new_node == NULL)
    {
        perror("malloc");
        return;
    }
    strcpy(new_node->key,key);
    strcpy(new_node->value,value);
    new_node->next = self->buckets[index];
    self->buckets[index] = new_node;
}

static const char *get_impl(hash_table *self,const char *key)
{
    if(self == NULL)
    {
        return NULL;
    }
    unsigned index = hash_func(key,self->capacity);
    hash_node *curr = self->buckets[index];
    while(curr != NULL)
    {
        if(strcmp(curr->key,key) == 0)
        {
            return curr->value;
        }
        curr = curr->next;
    }
    return NULL;
}

static void destroy_impl(hash_table *self)
{
    if(self != NULL)
    {
        for(int i=0;i<self->capacity;++i)
        {
            hash_node *curr = self->buckets[i];
            while(curr != NULL)
            {
                hash_node *temp = curr;
                curr = curr->next;
                free(temp);
            }
        }
        free(self->buckets);
        free(self);
    }
}

hash_table *hash_table_create(int capacity)
{
    if(capacity <= 0)
    {
        return NULL;
    }
    hash_table *ht = (hash_table*)malloc(sizeof(hash_table));
    if(ht == NULL)
    {
        perror("malloc");
        return NULL;
    }
    ht->capacity = capacity;
    ht->buckets =  (hash_node**)calloc(capacity,sizeof(hash_node*));
    if(ht->buckets == NULL)
    {
        perror("malloc");
        free(ht);
        return NULL;
    }
    ht->put = put_impl;
    ht->get = get_impl;
    ht->destroy = destroy_impl;
    return ht;
}