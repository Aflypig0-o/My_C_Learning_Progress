#include <stdio.h>
#include "AVLtree.h"

int main(void)
{
    int cases[4][3] = {
        {30, 20, 10},   /* LL */
        {10, 20, 30},   /* RR */
        {30, 10, 20},   /* LR */
        {10, 30, 20},   /* RL */
    };
    const char *name[4] = {"LL", "RR", "LR", "RL"};

    for (int c = 0; c < 4; c++)
    {
        AVLNode *r = NULL;
        printf("== %s ==", name[c]);
        for (int i = 0; i < 3; i++)
        {
            printf(" 插%d", cases[c][i]);
            fflush(stdout);
            r = insert(r, cases[c][i]);
            printf("(根=%d)", r ? r->data : -1);
            fflush(stdout);
        }
        printf("\n");
    }
    return 0;
}
