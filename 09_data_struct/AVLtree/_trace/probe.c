#include <stdio.h>
#include "AVLtree.h"
int main(void)
{
    AVLNode *r = NULL;
    r = insert(r, 30);
    printf("插30: root=%d\n", r->data);
    r = insert(r, 40);
    printf("插40: root=%d\n", r->data);
    r = insert(r, 50);
    printf("插50: root=%d\n", r ? r->data : -1);
    return 0;
}
