#ifndef HASH_H
#define HASH_H
#include <stdbool.h>
#include <stdio.h>

#define MAX_KEY_LEN 50
#define MAX_VAL_LEN 100

typedef struct hash_node hash_node;
typedef struct hash_table hash_table;

struct hash_node
{
    char key[MAX_KEY_LEN];
    char value[MAX_VAL_LEN];
    hash_node *next;
};

struct hash_table
{
    hash_node **buckets;
    int capacity;
    void (*put)(hash_table *self, const char *key, const char *value); // 插入/更新
    const char* (*get)(hash_table *self, const char *key);             // 查找
    void (*destroy)(hash_table *self);                                 // 销毁
};

hash_table *hash_table_create(int capacity);

#endif