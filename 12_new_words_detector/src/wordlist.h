#ifndef WORDLIST_H
#define WORDLIST_H
#include <stdbool.h>

#define MAX_WORDS 10000
#define MAX_WORD_LEN 32

typedef struct
{
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
}WorldList;

#endif